#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>


/* Количество ячеек вдоль координат x, y, z */
#define X_SIZE 20
#define Y_SIZE 20
#define Z_SIZE 20
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
		
		for (x = 1; x < X_SIZE; x++)
		{
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
		}

		iteration_cntr++;
	} while (!end);

	return iteration_cntr;
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
	double X = 2.0;
	double Y = 2.0;
	double Z = 2.0;
	
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

	return 0;
}