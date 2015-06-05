#include "main.h"


int DEBUG = 1;
int LAYER = 0;


int main(int argc, char **argv)
{
	int size;
	int rank;
	MATRIX *matrix = get_matrix_from_file("input.txt");
	MATRIX *vector = get_matrix(3, 1, ({ { 1 }, { 1 }, { 1 } }));
	MATRIX *result;

	show_matrix(matrix);
	show_matrix(vector);

	result = multiply_matrixes(matrix, vector);

	show_matrix(result);

	// MPI_Init(&argc, &argv);
	// MPI_Comm_size(MPI_COMM_WORLD, &size);
	// MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// printf("MPI:\n   size: %d\n   rank: %d\n", size, rank);

	// MPI_Finalize();

	delete_matrix(matrix);
	delete_matrix(vector);
	return 0;
}
