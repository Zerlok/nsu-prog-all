#include <stdarg.h>
#include <stdlib.h>

#include "class.h"


void *new(void *_class, va_list *args)
{
	const Class *cls = _class;
	void *ptr_obj = malloc(cls->size);
	*(const Class**)ptr_obj = cls;

	if (cls->constructor == NULL)
		return ptr_obj;

	va_start(*args, _class);
	ptr_obj = cls->constructor(ptr_obj, &args);
	va_end(*args);

	return ptr_obj;
}


void delete(void *ptr_obj)
{
	if (ptr_obj == NULL)
		return;

	Class *cls = ptr_obj;

	if (cls->destructor != NULL)
		ptr_obj = cls->destructor(ptr_obj);

	free(ptr_obj);
}


void print(void *ptr_obj)
{
	Class *cls = ptr_obj;

}
