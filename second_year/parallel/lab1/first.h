#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


#define EPSILON 0.00001
#define POSITIVE_TAU  0.01
#define NEGATIVE_TAU -0.01

#define TAG_SEND_MATRIX 100
#define TAG_SEND_OFFSET 101
#define TAG_SEND_LENGTH 102

#define SIZE 100


int mpi_rank;
int mpi_size;
int chunks_num;
int displs_num;


double A[SIZE * SIZE];
double Y[SIZE];
double B[SIZE];


double init_matrix(double *matrix);
double read_matrix_column(double column[SIZE]);
double read_matrxi_row(double row[SIZE]);
double get_vector_norma(double *vector);

void calculate_result();

double print_vector(double vector[SIZE]);
double print_matrix(double vector[SIZE]);


int get_chunk_size(int rank)
{
	return ((SIZE / mpi_size)
			+ (rank < (SIZE % mpi_size) ? 1 : 0));
}


double init_matrix(double *matrix)
{
	int chunk_size = c_recvcounts[rank];
	double* chunk = (double*) calloc(chunk_size * SIZE, sizeof(double));
	int shift = c_displs[rank];
	for (int i = 0; i < chunk_size; i++) {
		for (int j = 0; j < N; j++) {
			chunk[i * N + j] = (i == (j - shift)) ? 2 : 1;
		}
	}
	return chunk;	
}