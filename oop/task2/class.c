#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "class.h"


void *new(void *_class, ...)
{
	Class *cls = _class;
	void *ptr_obj = malloc(cls->size);
	memcpy(ptr_obj, cls, sizeof(Class));

	if (cls->constructor == NULL)
		return ptr_obj;

	va_list args;
	va_start(args, _class);

	printf("### Constructor : %p ###\n", ptr_obj);
	ptr_obj = cls->constructor(ptr_obj, &args);

	va_end(args);
	return ptr_obj;
}


void delete(void *ptr_obj)
{
	if (ptr_obj == NULL)
		return;

	Class *cls = ptr_obj;

	printf("### Destructor : %p ###\n", ptr_obj);
	if (cls->destructor != NULL)
		cls->destructor(ptr_obj);

	free(ptr_obj);
}


void print(void *ptr_obj)
{
	if (ptr_obj == NULL)
	{
		printf("%p\n", NULL);
		return;
	}

	Class *cls = ptr_obj;

	if (cls->printor != NULL)
		cls->printor(ptr_obj);

	else
		printf("[Class: %p : %ld]\n", cls, cls->size);
}
