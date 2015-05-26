#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
	int size;
	int rank;
	int a = 0;
	int b = 0;
	MPI_Status mpi_status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)
	{
		a = 10;
	}

	MPI_Bcast(&a, 1, MPI_INT, 0, MPI_COMM_WORLD);

	printf("MPI:\n   size: %d\n   rank: %d\n   {'a' : %d, 'b' : %d}\n--------------------\n", size, rank, a, b);

	MPI_Finalize();
	return 0;
}
