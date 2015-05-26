#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
	int size;
	int rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	printf("MPI:\n   size: %d\n   rank: %d\n", size, rank);
	printf("Hello, World!\n");

	MPI_Finalize();
	return 0;
}
