#include "main.h"
#include "matrix.h"


MATRIX *get_empty_matrix(size_t size_x, size_t size_y)
{
	size_t x;
	size_t y;

	MATRIX *mtrx = (MATRIX*)malloc(sizeof(MATRIX));
	mtrx->size_x = size_x;
	mtrx->size_y = size_y;

	mtrx->data = (double*)calloc(sizeof(double), size_x * size_y);
	for (x = 0; x < size_x; x++)
	{
		for (y = 0; y < size_y; y++)
		{
			mtrx->data[(size_y * x) + y] = 0.0;
		}
	}

	return mtrx;
}


MATRIX *multiply_matrix_and_vector(MATRIX *A, MATRIX *B)
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

	printf("creating matrix (%ld x %ld)\n", A->size_x, B->size_y);
	MATRIX *R = get_empty_matrix(A->size_x, B->size_y);

	for (x = 0; x < R->size_x; x++)
		for (i = 0; i < A->size_y; i++)
			R->data[x] += A->data[(A->size_y * x) + i] * B->data[i];
	
	return R;
}


MATRIX *get_row(size_t row_num, MATRIX *mtrx)
{
	if ((row_num < 0) || (row_num >= mtrx->size_x))
		return NULL;

	size_t i;
	MATRIX *row = get_empty_matrix(1, mtrx->size_y);
	// printf("Rowing matrix:\n");
	// show_matrix(mtrx);

	for (i = 0; i < mtrx->size_y; i++) {
		row->data[i] = mtrx->data[(mtrx->size_y * row_num) + i];
		// printf("rowed [%ld] [%ld]\n", (mtrx->size_y * row_num), i);
	}

	return row;
}


MATRIX *get_column(size_t col_num, MATRIX *mtrx)
{
	if ((col_num < 0) || (col_num >= mtrx->size_y))
		return NULL;

	size_t i;
	MATRIX *col = get_empty_matrix(mtrx->size_x, 1);

	// printf("COluming matrix:\n");
	// show_matrix(mtrx);

	for (i = 0; i < mtrx->size_x; i++) {
		col->data[i] = mtrx->data[(mtrx->size_y * i) + col_num];
		// printf("columned [%ld] [%ld] = %f\n", (mtrx->size_y * i), col_num, col->data[i]);
	}

	return col;
}


MATRIX *get_matrix(size_t size_x, size_t size_y, double *values)
{
	if (values == NULL)
	{
		printf("No values were specified!\n");
		return NULL;
	}

	size_t x;
	size_t y;

	MATRIX *mtrx = get_empty_matrix(size_x, size_y);
	printf("%ldx%ld\n", mtrx->size_x, mtrx->size_y);

	for (x = mtrx->size_x; x > 0; x--)
	{
		for (y = mtrx->size_y; y > 0; y--)
		{
			// printf("[%ld, %ld]: %f", x - 1, y - 1, values[(mtrx->size_y * (x - 1)) + y - 1]);
			printf("%f ", values[(mtrx->size_y * (x - 1)) + y - 1]);
			mtrx->data[(mtrx->size_y * (x - 1)) + y - 1] = values[(mtrx->size_y * (x - 1)) + y - 1];
		}
		printf("\n");
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
			if (fscanf(file, "%lf", &(mtrx->data[(size_y * x) + y])) == EOF)
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

	printf("Matrix pointer: %p\n", mtrx);
	size_t x;
	size_t y;

	printf("Printing matrix (%ld x %ld)\n", mtrx->size_x, mtrx->size_y);
	for (x = 0; x < mtrx->size_x; x++)
	{
		for (y = 0; y < mtrx->size_y; y++)
		{
			printf("%.1lf ", mtrx->data[(mtrx->size_y * x) + y]);
		}

		printf("\n");
	}
}


void delete_matrix(MATRIX *mtrx)
{
	if ((mtrx == NULL)
		|| (mtrx->data == NULL))
		return;

	free(mtrx->data);
	free(mtrx);
}
