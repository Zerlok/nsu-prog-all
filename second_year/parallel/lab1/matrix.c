#include "main.h"
#include "matrix.h"


MATRIX *get_empty_matrix(size_t size_x, size_t size_y)
{
	size_t x;
	size_t y;

	MATRIX *mtrx = (MATRIX*)malloc(sizeof(MATRIX));
	mtrx->size_x = size_x;
	mtrx->size_y = size_y;

	mtrx->data = (double**)calloc(sizeof(double*), size_x);
	for (x = 0; x < size_x; x++)
	{
		mtrx->data[x] = (double*)calloc(sizeof(double), size_y);

		for (y = 0; y < size_y; y++)
		{
			mtrx->data[x][y] = 0.0;
		}
	}

	return mtrx;
}


MATRIX *multiply_matrixes(MATRIX *A, MATRIX *B)
{
	if (A->size_y != B->size_x)
	{
		printf("Cannot multiply matrixes (wrong sizes: %ldx%ld %ldx%ld).\n", A->size_x, A->size_y, B->size_x, B->size_y);
		return NULL;
	}

	size_t x;
	size_t y;
	size_t i;
	double sum;
	double res;

	MATRIX *R = get_empty_matrix(A->size_x, B->size_y);

	for (x = 0; x < R->size_x; x++)
	{
		for (y = 0; y < R->size_y; y++)
		{			
			for (i = 0; i < A->size_y; i++)
			{
				R->data[x][y] += A->data[x][i] * B->data[i][y];
			}
		}
	}

	// printf("Calculating [%ld][%ld]\n", x, y);
	// for (i = 0; i < A->size_y; i++)
	// {
	// 	printf("Adding [%ld][%ld] * [%ld][%ld] = ", i, y, x, i);
	// 	res = A->data[x][i] * B->data[i][y];
	// 	sum += res;
	// 	printf("%f\n", res);
	// }

	return R;
}


MATRIX *get_row(size_t row_num, MATRIX *mtrx)
{
	if ((row_num < 0) || (row_num >= mtrx->size_x))
		return NULL;

	size_t i;
	MATRIX *row = get_empty_matrix(1, mtrx->size_y);

	for (i = 0; i < mtrx->size_y; i++)
		row->data[0][i] = mtrx->data[row_num][i];

	return row;
}


MATRIX *get_column(size_t col_num, MATRIX *mtrx)
{
	if ((col_num < 0) || (col_num >= mtrx->size_y))
		return NULL;

	size_t i;
	MATRIX *col = get_empty_matrix(mtrx->size_x, 1);

	for (i = 0; i < mtrx->size_x; i++)
		col->data[i][0] = mtrx->data[i][col_num];

	return col;
}


void send_matrix(MATRIX *mtrx, int to)
{
	printf("Sending matrix [%ld][%ld] to %d.\n", mtrx->size_x, mtrx->size_y, to);
	
	// MPI_Send([variable] [length] [type] [reciever] [id] [communicator]);
	MPI_Send(&(mtrx->size_x), 1, MPI_INT, to, 17, MPI_COMM_WORLD);
	MPI_Send(&(mtrx->size_y), 1, MPI_INT, to, 17, MPI_COMM_WORLD);

	printf("Matrix values: %f\n", mtrx->data[0][0]);
	MPI_Send((mtrx->data), (mtrx->size_x * mtrx->size_y), MPI_DOUBLE, to, 17, MPI_COMM_WORLD);
}


MATRIX *recieve_matrix(int from)
{
	size_t size_x;
	size_t size_y;
	double **values;

	printf("Recieving matrix from %d.\n", from);

	// MPI_Recv([variable] [length] [type] [reciever] [id] [communicator] [status]);
	MPI_Recv(&size_x, 1, MPI_INT, from, 17, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(&size_y, 1, MPI_INT, from, 17, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	printf("Matrix [%ld][%ld].\n", size_x, size_y);
	MPI_Recv(values, (size_x * size_y), MPI_DOUBLE, from, 17, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	printf("Matrix values: %f.\n", **values);
	return get_matrix(size_x, size_y, values);
}


MATRIX *get_matrix(size_t size_x, size_t size_y, double **values)
{
	if (values == NULL)
	{
		printf("No values were specified!\n");
		return NULL;
	}

	size_t x;
	size_t y;

	MATRIX *mtrx = get_empty_matrix(size_x, size_y);

	for (x = 0; x < mtrx->size_x; x++)
	{
		for (y = 0; y < mtrx->size_y; y++)
		{
			mtrx->data[x][y] = values[x][y];
		}
	}
}


MATRIX *get_matrix_from_file(char *filename)
{
	size_t x;
	size_t y;
	size_t size_x;
	size_t size_y;
	MATRIX *mtrx;

	FILE *file = fopen(filename, "r");

	if (file == NULL)
	{
		printf("Cannot open the file.\n");
		return NULL;
	}

	if (fscanf(file, "%ld %ld", &size_x, &size_y) == EOF)
	{
		printf("Error while reading the size of matrix.\n");
		return NULL;
	}

	mtrx = get_empty_matrix(size_x, size_y);

	for (x = 0; x < size_x; x++)
	{
		for (y = 0; y < size_y; y++)
		{
			if (fscanf(file, "%lf", &(mtrx->data[x][y])) == EOF)
			{
				printf("Error while reading matrix data.\n");
				return NULL;
			}
		}
	}

	return mtrx;
}


void show_matrix(MATRIX *mtrx)
{
	if (mtrx == NULL)
		return;

	size_t x;
	size_t y;

	for (x = 0; x < mtrx->size_x; x++)
	{
		for (y = 0; y < mtrx->size_y; y++)
		{
			printf("%.1lf ", mtrx->data[x][y]);
		}

		printf("\n");
	}
}


void delete_matrix(MATRIX *mtrx)
{
	if ((mtrx == NULL)
		|| (mtrx->data == NULL))
		return;

	size_t x;
	size_t y;

	for (x = 0; x < mtrx->size_x; x++)
	{
		free(mtrx->data[x]);
	}
	
	free(mtrx->data);
	free(mtrx);
}
