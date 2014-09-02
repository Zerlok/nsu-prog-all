#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define LEN 101 // max vertices + 1


int was_here[LEN];
int matrix[LEN][LEN];


void init_was_here();
void init_matrix();
void show_looped_vertices_depth(int v, int *was_here);
// void show_looped_vertices_width(int v, int *was_here);
