#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "extrastring.h"


char **str_to_args(char *string)
{
	int argn = count_chars(string, ' ') + 1;
	char **args = (char**)calloc(argn, sizeof(char*));
	char *substr = strtok(string, " \n");
	int i;

	for (i = 0; i < argn; i++)
	{
		args[i] = (char*)calloc(strlen(substr)+1, sizeof(char));
		strcpy(args[i], substr);
		substr = strtok(NULL, " \n");
	}

	return args;
}


void delete_args(int argn, char **args)
{
	int i;
	for (i = argn-1; i >= 0; i--)
		free(args[i]);
}


size_t count_chars(char *string, char chr)
{
	if (string == NULL)
		return 0;

	size_t counter = 0;

	size_t i;
	for (i = 0; string[i] != 0; i++)
		if (string[i] == chr)
			++counter;

	return counter;
}
