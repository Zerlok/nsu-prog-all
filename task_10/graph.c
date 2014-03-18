#include "mod.h"


void print_help()
{
	printf("Write the name of input file and choose flag, how to show graph connections with 1st vertex.\n");
	printf("Flags:\n\t-d\t-\tDepth walk\n\t-w\t-\tWidth walk\n\t--help\t-\tTo show this help\n");
	printf("Example: input.txt -d\n");
}


void show_was_here()
{
	int i;

	printf("[");
	for (i = 1; i <= LEN; i++)
	{
		printf("%d ", was_here[i]);
	}
	printf("]\n");
}


void show_matrix()
{
	int i, j;

	for (i = 1; i <= LEN; i++)
	{
		for (j = 1; j <= LEN; j++)
		{
			printf("%d",matrix[i][j]);
			printf("\n");
		}
	}	
}


void init_was_here()
{
	int i;

	for (i = 1; i<= LEN; i++)
	{
		was_here[i] = 0;
	}
}

void init_matrix()
{
	int i, j;

	for (i = 1; i <= LEN; i++)
	{
		for (j = 1; j <= LEN;  j++)
		{
			matrix[i][j] = 0;
		}
	}

}

void show_looped_vertices_depth(int v, int *was_here)
{
	int i;
	was_here[v] = 1;
	 
	for (i = 1; i <= LEN; i++)
		{
			if (matrix[v][i] == 1 && was_here[i] == 0)
			{
				show_looped_vertices_depth(i, was_here);
			}
		}
	
	printf("[%d]", v);	
}


void show_looped_width(int *was_here)
{
	int i, steps = 0;

	int p = 1;

	while (p)
	{
		p = show_looped_vertices_width(1, steps, was_here);
		steps += 1;
	}
}


int show_looped_vertices_width(int v, int steps, int *was_heres)
/*
	Returns 0 if nothing was printed, otherwise 1
*/

{
	int i, printed = 0;
	
	if (steps > 0)
	{
		for (i = 1; i <= LEN; i++)
		{
			if (matrix[v][i] == 1)
			{
				if (show_looped_vertices_width(i, steps-1, was_here))
				{
					printed = 1;
				}
			}
		}

	}
	else if (was_here[v] == 0)
	{
		was_here[v] = 1;
		printf("[%d]", v);
		return 1;
	}
	return printed;
}
