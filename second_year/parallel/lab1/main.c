#include "main.h"


int DEBUG = 1;
int LAYER = 0;


int main(int argc, char **argv)
{
	int size;
	int rank;
	MPI_Status mpi_status;

	MATRIX *matrix1 = get_matrix_from_file("matrix1.txt");
	MATRIX *matrix2 = get_matrix_from_file("matrix2.txt");
	MATRIX *row;
	MATRIX *result;

	printf("First\n");
	show_matrix(matrix1);

	// MPI initialization.
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Requirements.
	if ((size != 3) && (rank == 0))
	{
		printf("only 3 cpus should be!\n");
		return 1;
	}

	row = get_column(rank, matrix2);

	// Tell about this cpu.
	printf("MPI:\n   size: %d\n   rank: %d\n", size, rank);
	show_matrix(row);

	result = multiply_matrixes(matrix1, row);

	if (rank != 0)
	{
		send_matrix(result, 0);
	}
	else
	{
		printf("Col1\n");
		show_matrix(result);
		result = recieve_matrix(1);
		show_matrix(result);
		result = recieve_matrix(2);
		show_matrix(result);
	}

	// printf("Result\n");
	// show_matrix(result);

	delete_matrix(matrix1);
	delete_matrix(matrix2);
	delete_matrix(result);

	MPI_Finalize();
	return 0;
}
