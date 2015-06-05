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
	double sum;

	MATRIX *R = get_empty_matrix(A->size_x, B->size_y);

	for (x = 0; x < R->size_x; x++)
	{
		for (y = 0; y < R->size_y; y++)
		{
			R->data[x][y] += A->data[x][y] * B->data[y][x];
		}
	}

	return R;
}


MATRIX *get_matrix(size_t size_x, size_t size_y, double **values)
{
	if (values == NULL)
	{
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
