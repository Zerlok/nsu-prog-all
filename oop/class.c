#include <stdlib.h>

#include "class.h"


void *new(const void *_class...)
{
	const struct Class *class = _class;
	void *ptr = malloc(class->size);
	*(const struct Class **)ptr = class;

	// ...

	return ptr;
}
