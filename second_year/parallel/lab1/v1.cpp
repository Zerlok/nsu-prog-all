#include <mpi.h>
#include <cstdio>
#include <cstdlib>


#define EPS 0.00001
#define TAU 0.00001


#define SIZE 10


int mpi_size, mpi_rank;

int* CHUNKS; // chunks sizes
int* POSS; // chunks positions


int get_chunk_size(int given_rank);
int calculate_shift(int given_rank);


double *create_matrix();
double *create_vector();


double *subtract_vector_from_vector(double* a, double* b);
double *multiply_scalar_by_vector(double scalar, double* vector);
double *multiply_matrix_by_vector(double* matrix, double* vector);
double squared_norm_of_vector(double* vector);


double* calculate(double* matrix, double* vector);


int* count_chunks();
int* count_poss();


int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

	POSS = count_poss();
	CHUNKS = count_chunks();

	double* matrix = create_matrix();
	double* vector = create_vector();
	//print_vector(vector);

	double start_time = MPI_Wtime();
	double *result = calculate(matrix, vector);
	double end_time = MPI_Wtime();

	// print_vector(result);
	printf("PROCESS: %d TIME: %f\n", mpi_rank, end_time - start_time);

	free(matrix);
	free(vector);
	free(result);

	MPI_Finalize();
	return 0;
}

int get_chunk_size(int given_rank)
{
	int basic_chunk = SIZE / mpi_size;
	int rest = SIZE % mpi_size;
	return basic_chunk + (given_rank < rest ? 1 : 0);
}

int calculate_shift(int given_rank)
{
	int result = 0;
	for (int i = 0; i < given_rank; i++)
	{
		result += get_chunk_size(i);
	}
	return result;
}

double* create_matrix()
{
	int chunk_size = CHUNKS[mpi_rank];
	double* chunk = (double*) calloc(chunk_size * SIZE, sizeof(double));
	int shift = POSS[mpi_rank];
	for (int i = 0; i < chunk_size; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			chunk[i * SIZE + j] = (i == (j - shift)) ? 2 : 1;
		}
	}
	return chunk;
}

double* create_vector()
{
	int chunk_size = CHUNKS[mpi_rank];
	double* vector = (double*) calloc(chunk_size, sizeof(double));
	for (int i = 0; i < chunk_size; i++)
	{
		vector[i] = SIZE + 1;
	}
	return vector;
}

// sizes
int* count_chunks()
{
	int* counts = (int*) calloc(mpi_size, sizeof(int));
	
	for (int i = 0; i < mpi_size; i++)
	
		counts[i] = get_chunk_size(i);
	
	return counts;
}

// positions
int* count_poss()
{
	int* counts = (int*) calloc(mpi_size, sizeof(int));
	counts[0] = 0;

	for(int i = 1; i < mpi_size; i++)
		counts[i] = counts[i - 1] + get_chunk_size(i);

	return counts;
}


double squared_norm_of_vector(double* vector)
{
	double sum;
	double chunk_sum = 0;
	
	for (int i = 0; i < CHUNKS[mpi_rank]; i++)
	{
		chunk_sum += vector[i] * vector[i];
	}

	// Combines values from all processes and distributes the result back to all processes
	// sendbuf, recvbuf, count, datatype, oper, comm
	MPI_Allreduce(&chunk_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	return sum;
}


double* subtract_vector_from_vector(double* a, double* b)
{
	double* result = (double*) calloc(CHUNKS[mpi_rank], sizeof(double));
	
	for (int i = 0; i < CHUNKS[mpi_rank]; i++)
	{
		result[i] = a[i] - b[i];
	}
	
	return result;
}


double* multiply_scalar_by_vector(double scalar, double* vector)
{
	double* result = (double*) calloc(CHUNKS[mpi_rank], sizeof(double));
	
	for (int i = 0; i < CHUNKS[mpi_rank]; i++)
	{
		result[i] = scalar * vector[i];
	}

	return result;
}


double* multiply_matrix_by_vector(double* matrix, double* vector)
{
	int vector_length = CHUNKS[mpi_rank];
	int offset = POSS[mpi_rank];
	int incoming_process_data = 0;

	double* result = (double*) calloc(vector_length, sizeof(double));
	double* v = (double*) calloc(SIZE/mpi_size + 1, sizeof(double));
	
	for (int i = 0; i < vector_length; i++)
	{
		v[i] = vector[i];
	}
	
	for (int i = 0; i < mpi_size; i++)
	{
		// index of current part of vector
		incoming_process_data = (mpi_rank + i) % mpi_size;

		for (int i = 0; i < CHUNKS[mpi_rank]; i++)
		{
			for (int j = 0; j < CHUNKS[incoming_process_data]; j++)
			{
				result[i] += matrix[i * SIZE + j + POSS[incoming_process_data]] * v[j];
			}
		}

		// switch vector, (vector length, vector offset) between processes
		// Sends and receives using a single buffer
		// buf, count, datatype, dest, sendtag, source, recvtag, comm, status
		MPI_Sendrecv_replace(v, SIZE/mpi_size + 1, MPI_DOUBLE, (mpi_rank+1) % mpi_size, 100,
			(mpi_rank-1) % mpi_size, 100, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	return result;
}


double* calculate(double* matrix, double* vector)
{
	double* result = (double*) calloc(SIZE, sizeof(double));
	// Just a little optimization
	double vector_squared_norm = squared_norm_of_vector(vector);
	while (1)
	{
		// Ax
		double* z = multiply_matrix_by_vector(matrix, result);
		// Ax - b
		double* y = subtract_vector_from_vector(z, vector);
		double norm = squared_norm_of_vector(y);
		
		if (norm/vector_squared_norm < EPS*EPS)
		{
			free(y);
			free(z);
			break;
		}

		// t(Ax - b)
		double* v = multiply_scalar_by_vector(TAU, y);
		
		// x - t(Ax - b)
		result = subtract_vector_from_vector(result, v);
		free(v);
	}
	return result;
}