#include <omp.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "second.h"


int CHUNK_SIZE;


double matrix[SIZE * SIZE];
double vector[SIZE];
double result[SIZE];

double u[SIZE];
double w[SIZE];
double v[SIZE];


void init_matrix();
void init_main_vectors();
void init_zero_vectors();
void calculate_result();

void show_matrix();
void show_vector(double vector[SIZE]);


void init_matrix()
{
	int x;
	int y;

	for (x = 0; x < SIZE; x++)
		for (y = 0; y < SIZE; y++)
			matrix[(x * SIZE) + y] = ((x == y) ? 2 : 1);
}

void init_main_vectors()
{
	for (int x = 0; x < SIZE; x++)
	{
		vector[x] = SIZE + 1;
		result[x] = 0;
	}
}


void init_zero_vectors()
{
	for (int x = 0; x < SIZE; x++)
	{
		u[x] = 0;
		w[x] = 0;
		v[x] = 0;
	}
}

void show_matrix()
{
	int x;
	int y;

	for (x = 0; x < SIZE; x++)
	{
		for (y = 0; y < SIZE; y++)
		{
			printf("%0.0f ", matrix[(x * SIZE) + y]);
		}
		printf("\n");
	}
}

void show_vector(double vector[SIZE])
{
	for (int x = 0; x < SIZE; x++)
		printf("%0.4f\n", vector[x]);
}


inline bool check_criteria(double sqr_norma1, double sqr_norma2)
{
	return ((sqr_norma1 / sqr_norma2)
			< (EPS * EPS));
}

void calculate_result()
{
	int x;
	int y;
	int offset;

	bool end = false;
	
	double w_sqr_norma = 0;
	double v_sqr_norma = 0;

	for (x = 0; x < SIZE; x++)
		v_sqr_norma += vector[x] * vector[x];
	
	#pragma omp parallel private(x, y) shared(end, w_sqr_norma)
	while (!end)
	{	
		#pragma omp single
		{
			init_zero_vectors();
			w_sqr_norma = 0;
		}

		// Ax
		#pragma omp for schedule(static, CHUNK_SIZE)
		for (x = 0; x < SIZE; x++)
		{
			offset = SIZE * x;
			for (y = 0; y < SIZE; y++)
				u[x] += matrix[offset + y] * result[y];
		}

		// Ax - b
		#pragma omp for schedule(static, CHUNK_SIZE)
		for (x = 0; x < SIZE; x++)
			w[x] = u[x] - vector[x];

		#pragma omp for reduction(+:w_sqr_norma)
		for (x = 0; x < SIZE; x++)
			w_sqr_norma += w[x] * w[x];

		// t(Ax - b)
		#pragma omp for schedule(static, CHUNK_SIZE)
		for (int x = 0; x < SIZE; x++)
			v[x] = TAU * w[x];

		// x - t(Ax - b)
		#pragma omp for schedule(static, CHUNK_SIZE)
		for (int x = 0; x < SIZE; x++)
			result[x] = result[x] - v[x];
		
		#pragma omp single
		end = check_criteria(w_sqr_norma, v_sqr_norma);
	}
}


int main(int argc, char **argv)
{
	init_matrix();
	init_main_vectors();

	CHUNK_SIZE = SIZE / omp_get_num_threads();
	
	double time_start = omp_get_wtime();
	calculate_result();
	double time_end = omp_get_wtime();
	// show_vector(result);
	printf("%f\n", time_end - time_start);

	return 0;
}
