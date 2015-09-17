#include <stdarg.h>
#include <stdlib.h>

#include "class.h"


void *new(const void *_class, ...)
{
	const Class *_cls = _class;
	void *ptr_obj = malloc(_cls->size);
	*(const Class**)ptr_obj = _cls; // ???

	if (_cls->constructor == NULL)
		return ptr_obj;

	va_list args;
	va_list(args, _class);
	_cls->constructor(ptr_obj, &args);
	va_end(args);

	return ptr_obj;
}


void delete(void *_object)
{
	if (_object == NULL)
		return;

	Class *_cls = _object->cls;
	_cls->destructor(_object);

	free(_object);
}
