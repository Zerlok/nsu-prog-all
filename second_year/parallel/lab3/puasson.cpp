#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>


/* Количество ячеек вдоль координат x, y, z */
#define X_SIZE 2
#define Y_SIZE 2
#define Z_SIZE 2
#define ALPHA 1
#define EPS 0.01


/* Макрос определения точного решения */
#define Fresh(x, y, z)(((x) + (y) + (z)))
/* Макрос задания правой части уравнения */
#define Ro(x, y, z)((-ALPHA * ((s) + (y) + (z))))
/* Macros for asking data from array cell */
#define Element(array, n, x, y, z, xn, yn, zn)(\
	((array)[(z)\
		+ (y) * (zn)\
		+ (x) * (yn) * (zn)\
		+ (n) * (xn) * (zn) * (yn)\
	])\
)


/* Выделение памяти для 3D пространства для текущей и предыдущей итерации */
double Func[2][X_SIZE + 1][Y_SIZE + 1][Z_SIZE + 1];

/* Array sides (2 sides to save previous data and calculate a new) */
int side0 = 1, side1 = 0;
/* x, y, z steps sizes */
double x_step_size, y_step_size, z_step_size;

// MPI
int mpi_size;
int mpi_rank;


/* Функция инициализации границ 3D пространства */
void init_borders()
{
	int x, y, z;

	// for each: if cell is in border coordinate --> init iteration_cntr, else 0.
	for (x = 0; x <= X_SIZE; x++)
		for (y = 0; y <= Y_SIZE; y++)
			for (z = 0; z <= Z_SIZE; z++)
				Func[0][x][y][z] = Func[1][x][y][z] = (
						((x == 0)
						|| (y == 0)
						|| (z == 0)
						|| (x == X_SIZE)
						|| (y == Y_SIZE)
						|| (z == Z_SIZE))
						? Fresh(x * x_step_size, y * y_step_size, z * z_step_size)
						: 0
				);
}


int calculate()
{
	int x, y, z;

	double xF, yF, zF;
	
	double owx = pow(x_step_size, 2);
	double owy = pow(y_step_size, 2);
	double owz = pow(z_step_size, 2);
	double constant = 2/owx + 2/owy + 2/owz + ALPHA;

	int end;
	int iteration_cntr = 0;
	/* Основной итерационный цикл */
	do
	{
		end = 1;
		side0 = 1 - side0;
		side1 = 1 - side1;
		
		MPI_Iallreduce(&wantEnd, (int*)&wantsEnd, 1,
				MPI_INT, MPI_LAND, MPI_COMM_WORLD, &reduceR);

		if (mpi_rank != 0)
		{
			wantEnd &= !slice(L1, 1, xn, yn, zn, disp, data, owx, owy, owz, hx, hy, hz, c, eps); //проверяем на конец решения
			MPI_Isend(&Element(data, L1, 1, 0, 0, xn, yn, zn), yn * zn, MPI_FLOAT, mpi_rank - 1,
					0, MPI_COMM_WORLD, &sbotR);
		}
		
		if (mpi_rank < (mpi_size - 1))
		{
			wantEnd &= !slice(L1, xn - 2, xn, yn, zn, disp, data, owx, owy, owz, hx, hy, hz, c, eps);
			MPI_Isend(&Element(data, L1, xn - 2, 0, 0, xn, yn, zn), yn * zn, MPI_FLOAT, mpi_rank + 1,
					0, MPI_COMM_WORLD, &stopR);
		}

		if (mpi_rank)
			MPI_Irecv(&Element(data, L1, 0, 0, 0, xn, yn, zn), yn * zn, MPI_FLOAT, mpi_rank - 1, 0, MPI_COMM_WORLD,&rtopR);
		
		if (mpi_rank < (mpi_size - 1))
			MPI_Irecv(&Element(data, L1, xn - 1, 0, 0, xn, yn, zn), yn * zn, MPI_FLOAT, mpi_rank + 1, 0, MPI_COMM_WORLD, &rbotR);
		
		for(x = 1 + !!mpi_rank; x < xn - (mpi_rank < (mpi_size - 1)) * 2 - 1; x++)
			wantEnd &= !slice(L1, x, xn, yn, zn, disp, data, owx, owy, owz, hx, hy, hz, c, eps);
		
		// wait for sending
		MPI_Wait(&reduceR, &tmp);
		
		if (mpi_rank)
		{
			MPI_Wait(&rtopR, &tmp);
			MPI_Wait(&sbotR, &tmp);
		}

		if (mpi_rank < (mpi_size - 1))
		{
			MPI_Wait(&stopR, &tmp);
		}

		iteration_cntr++;

		MPI_Allreduce(&end, (int*)&end, 1, MPI_INT, MPI_LAND, MPI_COMM_WORLD);
	} while (!end);



	return iteration_cntr;
}


int slice_calc()
{
	int end;
	int iteration_cntr = 0;
	/* Основной итерационный цикл */
	do
	{
		end = 1;
		side0 = 1 - side0;
		side1 = 1 - side1;
		
		for (y = 1; y < Y_SIZE; y++)
		{
			for (z = 1; z < Z_SIZE; z++)
			{
				xF = (Func[side0][x + 1][y][z] + Func[side0][x - 1][y][z]) / owx;
				yF = (Func[side0][x][y + 1][z] + Func[side0][x][y - 1][z]) / owy;
				zF = (Func[side0][x][y][z + 1] + Func[side0][x][y][z - 1]) / owz;

				Func[side1][x][y][z] = (
							(xF + yF + zF
							- Ro(x * x_step_size, y * y_step_size, z * z_step_size))
						/ constant);
			
				if(fabs(Func[side1][x][y][z] - Func[side0][x][y][z]) > EPS)
					end = 0;
			}
		}
	} while (!end);
}


/* Нахождение максимального расхождения полученного приближенного решения
 * и точного решения */
void find_func_max(double *maximum_diff double *maximum_x, double *maximum_y, double *maximum_z)
{

	double max_diff = 0.0;
	double absdiff;

	int max_x = 0, max_y = 0, max_y = 0;
	int x, y, z;
	
	for (x = 1; x < X_SIZE; x++)
	{
		for (y = 1; y < Y_SIZE; y++)
		{
			for (z = 1; z < Z_SIZE; z++)
			{
				absdiff = fabs(Func[side1][x][y][z]- Fresh(x * x_step_size, y * y_step_size, z * z_step_size));
				
				if (absdiff > max_diff)
				{
					// Update maximum
					max_diff = absdiff;
					max_x = x;
					max_y = y;
					max_z = z;
				}
			}
		}
	}

	(*maximum_diff) = max_diff;
	(*maximum_x) = max_x;
	(*maximum_y) = max_y;
	(*maximum_z) = max_z;
}


int main()
{
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

	double X = 2.0;
	double Y = 2.0;
	double Z = 2.0;
	
	int xn = get_chunk_size(mpi_rank, mpi_size, X_SIZE) + !!mpi_rank + (mpi_rank < mpi_size - 1);
	int yn = Y_SIZE;
	int zn = Z_SIZE;

	/* Размеры шагов */
	x_step_size = X / X_SIZE;
	y_step_size = Y / Y_SIZE;
	z_step_size = Z / Z_SIZE;

	struct timeval tstart, tend;
	gettimeofday(&tstart,(struct timezone*)0);

	init_borders();
	int iterations_num = calculate();
	
	gettimeofday(&tend,(struct timezone*)0);

	long int wrktime = (tend.tv_sec - tstart.tv_sec) * 1000000 + tend.tv_usec - tstart.tv_usec;
	printf("\nX_SIZE: %d iterations: %d eps: %f time: %ld\n", X_SIZE, iterations_num, EPS, wrktime);

	double func_max;
	double func_max_at_x, func_max_at_y, func_max_at_z;
	find_func_max(&func_max, &func_max_at_x, &func_max_at_y, &func_max_at_z);
	printf("Max differ: %f at (%d,%d,%d)\n",
			func_max,
			func_max_at_x,
			func_max_at_y,
			func_max_at_z
	);

	MPI_Finalize();
	return 0;
}