#include <mpi.h>
#include <cstdio>
#include <cstdlib>


#define EPS 0.00001
#define TAU 0.00001


#define SIZE 10


int mpi_size, mpi_rank;

// creates array that represents part of array
double* create_matrix();

//creates vector
double* create_vector();

// calculates number of rows that will belong 
// to process of given mpi_rank
int get_chunk_size(int given_rank);

// calculates vertical position of the first element
int calculate_shift(int given_rank);


double *multiply_matrix_by_vector(double* matrix, double* vector);
double *subtract_vector_from_vector(double* a, double* b);
double *multiply_scalar_by_vector(double scalar, double* vector);
double squared_norm_of_vector(double* vector);


double* calculate(double* matrix, double* vector);


int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

	double* matrix = create_matrix();
	double* vector = create_vector();

	//print_matrix(matrix);
	double start_time = MPI_Wtime();
	double *result = calculate(matrix, vector);
	double end_time = MPI_Wtime();

	//print_vector(result);
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
	int chunk_size = get_chunk_size(mpi_rank);
	double* chunk = (double*) calloc(chunk_size * SIZE, sizeof(double));
	int shift = calculate_shift(mpi_rank);
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
	double* vector = (double*) calloc(SIZE, sizeof(double));
	for (int i = 0; i < SIZE; i++)
	{
		vector[i] = SIZE + 1;
	}
	return vector;
}


double* subtract_vector_from_vector(double* a, double* b)
{
	double* result = (double*) calloc(SIZE, sizeof(double));
	for (int i = 0; i < SIZE; i++)
	{
		result[i] = a[i] - b[i];
	}
	return result;
}


double* multiply_scalar_by_vector(double scalar, double* vector)
{
	double* result = (double*) calloc(SIZE, sizeof(double));
	for (int i = 0; i < SIZE; i++)
	{
		result[i] = scalar * vector[i];
	}
	return result;
}


double squared_norm_of_vector(double* vector)
{
	double sum = 0;
	for (int i = 0; i < SIZE; i++)
	{
		sum += vector[i] * vector[i];
	}
	return sum;
}


// sizes
int* count_chunks()
{
	int* counts = (int*) calloc(mpi_size, sizeof(int));
	for (int i = 0; i < mpi_size; i++)
	{
		counts[i] = get_chunk_size(i);
	}
	return counts;
}

// positions
int* count_poss()
{
	int* counts = (int*) calloc(mpi_size, sizeof(int));
	for(int i = 0; i < mpi_size; i++)
	{
		counts[i] = calculate_shift(i);
	}
	return counts;
}


double* multiply_matrix_by_vector(double* matrix, double* vector)
{
	int chunk_size = get_chunk_size(mpi_rank);
	double* result = (double*) calloc(chunk_size, sizeof(double));

	for (int i = 0; i < chunk_size; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			result[i] += matrix[SIZE * i + j] * vector[j];
		}
	}
	
	return result;
}


double* calculate(double* matrix, double* vector)
{
	double* result = (double*) calloc(SIZE, sizeof(double));

	int* c_displs = count_poss();
	int* c_recvcounts = count_chunks();
	while (1)
	{
		// Ax
		double* u = multiply_matrix_by_vector(matrix, result);
		
		// Так как мы умножаем строку на весь вектор в каждом процессе, 
		// то нужно получить весь вектор в каждом процессе
		double* z = (double*) calloc(SIZE, sizeof(double));

		// Gathers data from all tasks and deliver the combined data to all tasks
		// sendbuf, sendcountm sendtype, recvbuf, recvcounts, displs, recvtype, comm
		MPI_Allgatherv(u, c_recvcounts[mpi_rank], MPI_DOUBLE, z, c_recvcounts, c_displs, MPI_DOUBLE, MPI_COMM_WORLD);

		// Ax - b
		double* y = subtract_vector_from_vector(z, vector);
		if (squared_norm_of_vector(y)/squared_norm_of_vector(vector) < EPS*EPS)
		{
			free(u);
			free(y);
			free(z);
			break;
		}

		// t(Ax - b)
		double* v = multiply_scalar_by_vector(TAU,y);
		// x - t(Ax - b)
		result = subtract_vector_from_vector(result, v);
	}
	return result;
}
