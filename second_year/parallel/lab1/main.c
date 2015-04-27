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
		result = multiply_matrixes(m1, col);
		printf("Resulting:\n");
		show_matrix(result);
	}

	delete_matrix(m1);
	delete_matrix(m2);
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
	{
		test(matrix1, matrix2);
		return 1;
	}

	col = get_column(rank, matrix2);
	result = multiply_matrixes(matrix1, col);
	MPI_Gather(result->data, matrix1->size_x, MPI_DOUBLE,
				values, matrix1->size_x, MPI_DOUBLE,
				0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		show_matrix(get_matrix(matrix1->size_x, matrix2->size_y, values));
	}

	// delete_matrix(matrix1);
	// delete_matrix(matrix2);
	// delete_matrix(result);

	MPI_Finalize();
	return 0;
}
