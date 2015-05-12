#include "main.h"


void test(MATRIX *m1, MATRIX *m2)
{
	int c;
	MATRIX *col;
	MATRIX *result;

	for (c = 0; c < m2->size_y; c++)
	{
		col = get_column(c, m2);
		// show_matrix(col);
		result = multiply_matrix_and_vector(m1, col);
		printf("Resulting:\n");
		show_matrix(result);
	}

	delete_matrix(m1);
	delete_matrix(m2);
	exit(0);
}


int main(int argc, char **argv)
{
	// MPI initialization.
	int size;
	int rank;
	MPI_Status mpi_status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Internal varialbles.
	MATRIX *matrix1 = get_matrix_from_file("matrix1.txt");
	MATRIX *matrix2 = get_matrix_from_file("matrix2.txt");
	MATRIX *col;
	MATRIX *result;
	double *values = (double*)calloc(sizeof(double), (matrix1->size_x * matrix2->size_y));

	if (rank == 0) {
		printf("Matrix 1\n");
		show_matrix(matrix1);

		printf("Matrix 2\n");
		show_matrix(matrix2);
	}

	// Requirements.
	if ((size != matrix2->size_y) && (rank == 0))
		test(matrix1, matrix2);

	col = get_column(rank, matrix2);
	result = multiply_matrix_and_vector(matrix1, col);
	
	MPI_Gather(result->data, result->size_x, MPI_DOUBLE,
				values, result->size_x, MPI_DOUBLE,
				0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		printf("values pointer: %p\n", values);
		printf("value: %f\n", values[0]);
		printf("values length: %ld\n", result->size_x);
		printf("ends pointer: %p\n", values + (result->size_x * result->size_y));
		printf("ends value: %f\n", values[(result->size_x * result->size_y)]);
		// delete_matrix(result);
		result = get_matrix(matrix1->size_x, matrix2->size_y, values);
		show_matrix(result);
	}

	// delete_matrix(matrix1);
	// delete_matrix(matrix2);
	// delete_matrix(result);

	MPI_Finalize();
	return 0;
}
