#include <stdio.h>

#include "class.h"
#include "point.h"
#include "rectangle.h"


void *Rectangle_constructor(void *_self, va_list *args)
{
	RectangleStruct *self = _self;

	self->begin = new_object(Point, va_arg(args, int), va_arg(args, int));
	self->end = new_object(Point, va_arg(args, int), va_arg(args, int));

	return self;
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
	Rectangle_destructor,
	Rectangle_drawer
};


void *Rectangle = &RectangleClass;
