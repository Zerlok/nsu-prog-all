#include <stdio.h>
#include <string.h>

/* main.c */

int *init_was_here()
{
	int i;
	static int was_here[100];

	for (i = 1; i<= 100; i++)
	{
		was_here[i] = 0;
	}
	return was_here;
}

int **init_matrix()
{
	int i, j;
	static int matrix[100][100];

	// int *lst = matrix;

	for (i = 1; i <= 100; i++)
	{
		for (j = 1; j <= 100;  j++)
		{
			matrix[i][j] = 0;
		}
	}
	// return lst;
	return matrix;
}

void show_looped_vertices_depth(int v, int *was_here, int **matrix)
{
	int i;
	
	was_here[v] = 1;
	for (i = 1; i <= 100; i++)
	{
		if (matrix[v][i] && !was_here[i])
		{
			show_looped_vertices_depth(i, was_here, matrix);
		}
	}
	printf("%d", v);
}

void show_looped_vertices_width(int v)
{
	int i;
	printf("Hello!\n");
}


int main(int argc, char **argv)
{
	char FILE_NAME[255];
	FILE *fp;
	int ch;
	int i,j; // for matrix
	int *was_here;
	int **matrix_pointer;

	was_here = init_was_here();
	matrix_pointer = init_matrix();

	if (argc > 1 && strcmp("--help", argv[1])) 
	{
		printf("HELP WILL BE HERE\n");
	} 

	// if (argc != 3 )
	// {
	// 	printf("Error");
	// 	return 1;
	// }

	// strcpy(FILE_NAME, argv[1]);

	if((fp = fopen(argv[1], "r")) == NULL)
	{
		printf("Error");
		return 1;
	}

	/*
	 read from file and fill the matrix
	*/

	// while(ch = fgetc(fp) != EOF)
	// {
	// 	fscanf(fp, "%d %d\n", &i, &j);
	// 	matrix_pointer[i][j] = 1;
	// 	matrix_pointer[j][i] = 1;
	// }

	// show_looped_vertices_depth();

	return 0;
}

/* graph.c */