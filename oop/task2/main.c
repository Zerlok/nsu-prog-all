#include <stdio.h>

#include "class.h"
#include "point.h"
#include "circle.h"
#include "rectangle.h"
#include "factory.h"
#include "extrastring.h"


void run_from_file(FactoryStruct *factory, FILE *input)
{
	void *obj;
	size_t len;
	char *line = NULL;
	int argn;
	char **args;

	while (getline(&line, &len, input) != EOF)
	{
		if (line[0] == '\n')
			continue;

		argn = count_chars(line, ' ') + 1;
		args = str_to_args(line);
		obj = fct_create(factory, argn, args);

		if (obj == NULL)
		{
			printf("null\n");
			continue;
		}

		print(obj);
		printf("\n");

		delete_object(obj);
		delete_args(argn, args);
	}

	free(line);
}


int main(int argc, char **argv)
{
	FactoryStruct *factory = new_object(Factory);

	fct_register(factory, "point", Point);
	fct_register(factory, "circle", Circle);
	fct_register(factory, "rectangle", Rectangle);

	if (argc < 2)
	{
		printf("Registered objects: ");
		print(factory->data);
		printf("\n");
		run_from_file(factory, stdin);
	}
	else
	{
		FILE *input = fopen(argv[1], "r");
		run_from_file(factory, input);
		fclose(input);
	}

	delete_object(factory);
	return 0;
}
