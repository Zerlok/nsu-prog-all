#include "main.h"


int DEBUG = 1;
int LAYER = 0;


int main(int argc, char **argv)
{
	int size;
	int rank;
	MATRIX *matrix1 = get_matrix_from_file("matrix1.txt");
	MATRIX *matrix2 = get_matrix_from_file("matrix2.txt");
	// MATRIX *vector = get_matrix(3, 1, ({ { 1 }, { 1 }, { 1 } }));
	MATRIX *result;

	printf("First\n");
	show_matrix(matrix1);
	printf("Second\n");
	show_matrix(matrix2);
	// show_matrix(vector);

	result = multiply_matrixes(matrix1, matrix2);

	printf("Result\n");
	show_matrix(result);

	// MPI_Init(&argc, &argv);
	// MPI_Comm_size(MPI_COMM_WORLD, &size);
	// MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// printf("MPI:\n   size: %d\n   rank: %d\n", size, rank);

	// MPI_Finalize();

	delete_matrix(matrix1);
	delete_matrix(matrix2);
	delete_matrix(result);
	// delete_matrix(vector);
	return 0;
}
