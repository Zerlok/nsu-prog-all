#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

/* Количество ячеек вдоль координат x, y, z */
#define ALPHA 1
#define Element(data, i, x, y, z, xn, yn, zn) ((data)[(z) + (y) * (zn) + (x) * (yn) * (zn) + (i) * (xn) * (zn) * (yn)])

static const int MAX_X = 10;
static const int MAX_Y = 10;
static const int MAX_Z = 10;


/* Выделение памяти для 3D пространства для текущей и предыдущей итерации */
double F[2][MAX_X+1][MAX_Y+1][MAX_Z+1];
double hx, hy, hz;


/* Функция определения точного решения */
inline double Fresh(double x, double y, double z)
{
	return x + y + z;
}


/* Функция задания правой части уравнения */
inline double Ro(double x, double y, double z)
{
	return -ALPHA * (x + y + z);
}


// получаем рабочую область
inline int get_chunk_size(int rank, int mpi_size, int MAX_SIZE)
{
	return MAX_SIZE / mpi_size + ((rank < MAX_SIZE % mpi_size) ? 1 : 0);
}

/* Нахождение максимального расхождения полученного приближенного решения
* и точного решения 
*/
int slice(
		int L1,
		int x,
		int xn,
		int yn,
		int zn,
		int disp,
		double *data,
		double owx,
		double owy,
		double owz,
		double hx,
		double hy,
		double hz,
		double c,
		double eps)
{
	double Fx;
	double Fy;
	double Fz;

	int y, z;
	int result = 0;
	int L0 = !L1;
	
	for (y = 1; y < yn - 1; y++)
	{
		for (z = 1; z < zn - 1; z++)
		{
			Fx = (Element(data, L0, x + 1, y, z, xn, yn, zn) + Element(data, L0, x - 1, y, z, xn, yn, zn)) / owx;
			Fy = (Element(data, L0, x, y + 1, z, xn, yn, zn) + Element(data, L0, x, y - 1, z, xn, yn, zn)) / owy;
			Fz = (Element(data, L0, x, y, z + 1, xn, yn, zn) + Element(data, L0, x, y, z - 1, xn, yn, zn)) / owz;
			
			Element(data, L1, x, y, z, xn, yn, zn) = (Fx + Fy + Fz - Ro((x + disp)*hx,y*hy,z*hz)) / c;
			
			result |= fabs(Element(data, L1, x, y, z, xn, yn, zn) - Element(data, L0, x, y, z, xn, yn, zn)) > eps;
		}
	}

	return result;
}


int main(int argc, char **argv)
{
	double X, Y, Z;
	double owx, owy, owz, c, eps;
	double hx;
	double hy;
	double hz;

	int mpi_size;
	int mpi_rank;
	MPI_Status tmp;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

	int x, y, z, mx, my, mz;
	int xn = get_chunk_size(mpi_rank, mpi_size, MAX_X) + !!mpi_rank + (mpi_rank < mpi_size - 1);
	int yn = MAX_Y;
	int zn = MAX_Z;

	int cntr, L0, L1;
	long int wrktime;
	struct timeval tv1,tv2;

	cntr = 0;
	X = 2.0;
	Y = 2.0;
	Z = 2.0;
	eps = 0.00001;
	L0 = 1;
	L1 = 0;

	/* Размеры шагов */
	hx = X / MAX_X;
	hy = Y / MAX_Y;
	hz = Z / MAX_Z;

	int disp = 0;
	for (int i = 0; i < mpi_rank; i++)
		disp += get_chunk_size(i, mpi_size, MAX_X);
	disp -= !!mpi_rank;

	double *data = (double*) malloc((2 * xn * yn * zn) * sizeof(double));

	owx = pow(hx, 2);
	owy = pow(hy, 2);
	owz = pow(hz, 2);
	c = 2/owx + 2/owy + 2/owz + ALPHA;
	gettimeofday(&tv1,(struct timezone*)0);

	/* Инициализация границ пространства */
	for(x = 0; x < xn; x++)
		for(y = 0; y < yn; y++)
			for(z = 0; z < zn; z++)
				if ((y == (yn - 1)) || (z == (zn - 1)) || !y || !z)
					Element(data, 0, x, y, z, xn, yn, zn) = Element(data, 1, x, y, z, xn, yn, zn) = (disp + x)*hx + y*hy + z*hz;
				else
					Element(data, 0, x, y, z, xn, yn, zn) = Element(data, 1, x, y, z, xn, yn, zn) = 0.f;

	if (!mpi_rank)
		for (z = 0; z < zn; z++)
			for (int y = 0; y < yn; y++)
				Element(data, 0, 0, y, z, xn, yn, zn) = Element(data, 1, 0, y, z, xn, yn, zn) = disp*hx + y*hy + z*hz;

	if (mpi_rank == mpi_size - 1)
		for (z = 0; z < zn; z++)
			for (y = 0; y < yn; y++)
				Element(data, 0, xn - 1, y, z, xn, yn, zn) = Element(data, 1, xn - 1, y, z, xn, yn, zn) = (disp + xn - 1)*hx + y*hy + z*hz;


	/* Основной итерационный цикл */
	int end_found = 0;
	volatile int ends_found = 0;
	{
		MPI_Request stopR, sbotR, rtopR, rbotR;
		L0 = 1 - L0;
		L1 = 1 - L1;


		end_found = 1;
		if (mpi_rank)
		{
			end_found &= !slice(L1, 1, xn, yn, zn, disp, data, owx, owy, owz, hx, hy, hz, c, eps); //проверяем на конец решения
			MPI_Isend(&Element(data, L1, 1, 0, 0, xn, yn, zn), yn * zn, MPI_FLOAT, mpi_rank - 1,
				0, MPI_COMM_WORLD, &sbotR);
		}

		if (mpi_rank < (mpi_size - 1))
		{
			end_found &= !slice(L1, xn - 2, xn, yn, zn, disp, data, owx, owy, owz, hx, hy, hz, c, eps);
			MPI_Isend(&Element(data, L1, xn - 2, 0, 0, xn, yn, zn), yn * zn, MPI_FLOAT, mpi_rank + 1,
				0, MPI_COMM_WORLD, &stopR);
		}
		
		if (mpi_rank)
			MPI_Irecv(&Element(data, L1, 0, 0, 0, xn, yn, zn), yn * zn, MPI_FLOAT, mpi_rank - 1, 0, MPI_COMM_WORLD,&rtopR);
		
		if (mpi_rank < (mpi_size - 1))
			MPI_Irecv(&Element(data, L1, xn - 1, 0, 0, xn, yn, zn), yn * zn, MPI_FLOAT, mpi_rank + 1, 0, MPI_COMM_WORLD, &rbotR);
		
		for(x = 1 + !!mpi_rank; x < xn - (mpi_rank < (mpi_size - 1)) * 2 - 1; x++)
			end_found &= !slice(L1, x, xn, yn, zn, disp, data, owx, owy, owz, hx, hy, hz, c, eps);
		
		if (mpi_rank)
		{
			MPI_Wait(&rtopR, &tmp);
			MPI_Wait(&sbotR, &tmp);
		}

		if (mpi_rank < (mpi_size - 1))
		{
			MPI_Wait(&stopR, &tmp);
		}

		cntr++;

		// combines values from all processes and distributes the result back to all processes in ALPHA nonblocking way 
		MPI_Allreduce(&end_found, (int*)&ends_found, 1,
				MPI_INT, MPI_LAND, MPI_COMM_WORLD);
	}
	while (!end_found);

	gettimeofday(&tv2,(struct timezone*)0);
	wrktime = (tv2.tv_sec - tv1.tv_sec)*1000000 + tv2.tv_usec - tv1.tv_usec;
	printf("proc %d, x = %d xter = %d E = %f T = %ld\n", mpi_rank, xn, cntr, eps, wrktime);

	free(data);
	MPI_Finalize();
	return 0;
}
