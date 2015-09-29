#include <stdio.h>
#include <stdlib.h>

#include "class.h"
#include "point.h"
#include "rectangle.h"


void Rectangle_initializer(void *_self, StringArray *args)
{
	if ((args == NULL)
			|| (args->m_size < 5))
		return;

	RectangleStruct *self = _self;

	sa_print(args);
	self->begin = new_object(Point, atoi(sa_get(args, 1)), atoi(sa_get(args, 2)));
	self->end = new_object(Point, atoi(sa_get(args, 3)), atoi(sa_get(args, 4)));
}


void Rectangle_destructor(void *_self)
{
	RectangleStruct *self = _self;

	delete_object(self->begin);
	delete_object(self->end);
}


void Rectangle_drawer(void *_self)
{
	RectangleStruct *self = _self;

	print(self->begin);
	printf(", ");
	print(self->end);
}


Class RectangleClass = {
	sizeof(RectangleStruct),
	NULL,
	Rectangle_initializer,
	Rectangle_destructor,
	Rectangle_drawer
};


void *Rectangle = &RectangleClass;
