#include <stdio.h>

#include "class.h"
#include "point.h"
#include "circle.h"


void *Circle_constructor(void *_self, va_list *args)
{
	CircleStruct *self = _self;

	self->center = new_object(Point, va_arg(args, int), va_arg(args, int));
	self->radius = va_arg(args, int);

	return self;
}


void Circle_destructor(void *_self)
{
	CircleStruct *self = _self;
	delete_object(self->center);
}


void Circle_drawer(void *_self)
{
	CircleStruct *self = _self;

	print(self->center);
	printf(", r=%d", self->radius);
}


Class CircleClass = {
	sizeof(CircleStruct),
	Circle_constructor,
	Circle_destructor,
	Circle_drawer
};


void *Circle = &CircleClass;
