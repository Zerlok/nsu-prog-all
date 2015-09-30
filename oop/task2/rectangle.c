#include <stdio.h>
#include <stdlib.h>

#include "class.h"
#include "point.h"
#include "rectangle.h"


void *Rectangle_constructor(void *_self, va_list *args)
{
	RectangleStruct *self = _self;
	self->begin = NULL;
	self->end = NULL;

	return self;
}


void Rectangle_initializer(void *_self, int argn, char **args)
{
	if ((argn < 4)
			|| (args == NULL))
		return;

	RectangleStruct *self = _self;

	self->begin = new_object(Point, atoi(args[0]), atoi(args[1]));
	self->end = new_object(Point, atoi(args[2]), atoi(args[3]));
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
	Rectangle_constructor,
	Rectangle_initializer,
	Rectangle_destructor,
	Rectangle_drawer
};


void *Rectangle = &RectangleClass;
