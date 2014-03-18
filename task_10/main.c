#include "mod.h" 

int main(int argc, char **argv)
{
	FILE *file;
	char file_name[255];
	int ch;
	int i,j;

	/*	
		Argv reading.
	*/	

	if (argc == 1)
	{
		print_help();
		return 0;
	}
	
	if (argc > 1)
	{
		if (!(strcmp(argv[1], "--help")))
			{
				print_help();
				return 0;
			}
	}

	if (argc != 3 )
	{
		printf("Not enough arguments!\n");
		print_help();
		return 1;
	}

	strcpy(file_name, argv[1]);
	
	/*
		File reading.
	*/
	
	if((file = fopen(file_name, "r")) == NULL)
	{
		printf("Error while file opening!\n");
		exit(1);
	}

	while((fscanf(file, "%d %d", &i, &j)) != EOF)
	{
		matrix[i][j] = matrix[j][i] = 1;
	}
	fclose(file);

	/*
		Walking functions.
	*/

	if (!strcmp(argv[2], "-d"))
	{
		show_looped_vertices_depth(1, was_here);
	}
	else if (!strcmp(argv[2], "-w"))
	{
		printf("Will show in width\n");
		show_looped_width(was_here);
	}
	else if (!strcmp(argv[2], "--help"))
	{
		print_help();
	}
	else
	{
		printf("Unknown flag: '%s'\n", argv[2]);
		print_help();
	}
	printf("\n");
	return 0;
}
