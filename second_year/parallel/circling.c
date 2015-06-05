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

//	printf("MPI Total:\n   size: %d\n   rank: %d\n   {'a' : %d, 'b' : %d}\n", size, rank, a, b);

	// Doing the circle talking...

	if (rank == 0)
	{
		a = 1;
		b = 1;
	}

	do
	{

	// [variable] [length] [type] [from] [id] [communicator] [err_status]
	MPI_Recv(&b, 1, MPI_INT, (rank + size - 1) % size, 15, MPI_COMM_WORLD, &mpi_status);
	printf("Rank: [%d] ( Recieved: '%d' from [%d] )\n", rank, b, ((rank+size-1) % size));

	a = b;

	}
	while (a);

	while (b)
	{

	// [variable] [length] [type] [to] [id] [communicator]
	MPI_Send(&a, 1, MPI_INT, (rank + size + 1) % size, 15, MPI_COMM_WORLD);
	printf("Rank: [%d] ( Sent: '%d' to [%d] )\n", rank, a, ((rank+size+1) % size));

	}

	MPI_Finalize();
	return 0;
}
