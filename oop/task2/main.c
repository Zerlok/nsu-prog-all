#include <stdio.h>

#include "class.h"
#include "point.h"
#include "circle.h"
#include "rectangle.h"
#include "factory.h"
#include "extrastring.h"


int main(void)
{
	FactoryStruct *factory = new_object(Factory);

	fct_register(factory, "point", Point);
	fct_register(factory, "circle", Circle);
	fct_register(factory, "rectangle", Rectangle);

	printf("Registered objects: ");
	print(factory->data);
	printf("\n");

	void *obj;
	size_t len;
	char *line = NULL;
	String *args;

	while (getline(&line, &len, stdin) != EOF)
	{
		args = str_split(line, " \n");
		obj = fct_create(factory, args);

		if (obj == NULL)
		{
			printf("null object\n");
		}

		printf("Created object: ");
		print(obj);
		printf("\n");

		delete_object(obj);
		str_delete(args);
	}

	delete_object(factory);
	str_delete(args);

	return 0;
}
