#include "first.h"


int main(int argc, char **argv)
{

	double start_time = MPI_Wtime();
	calculate_result();
	double end_time = MPI_Wtime();

	print_vector(result);
	printf("PROCESS: %d TIME: %f\n", rank, end_time - start_time);

	return 0;
}
