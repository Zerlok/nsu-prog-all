#ifndef __MATRIX_H__
#define __MATRIX_H__


#define STD_SIZE 4


typedef struct MatrixStructure
{
	size_t size_x;
	size_t size_y;
	double **data;
} MATRIX;


MATRIX *get_empty_matrix(size_t size_x, size_t size_y);
MATRIX *get_matrix_from_file(char *filename);
MATRIX *multiply_matrixes(MATRIX *A, MATRIX *B);
MATRIX *get_matrix(size_t size_x, size_t size_y, double **values);
// void make_identity(MATRIX *mtrx);
void show_matrix(MATRIX *mtrx);
void delete_matrix(MATRIX *mtrx);


// __MATRIX_H__
#endif
