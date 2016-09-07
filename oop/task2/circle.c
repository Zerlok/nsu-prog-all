#include <stdio.h>
#include <stdlib.h>

#include "class.h"
#include "point.h"
#include "circle.h"


void *Circle_constructor(void *_self, va_list *args)
{
	CircleStruct *self = _self;
	self->center = NULL;
	self->radius = 0;

	return self;
}


void Circle_initializer(void *_self, int argn, char **args)
{
	if ((argn < 3)
			|| (args == NULL))
		return;

	CircleStruct *self = _self;

	self->center = new_object(Point, atoi(args[0]), atoi(args[1]));
	self->radius = atoi(args[2]);
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
	Circle_initializer,
	Circle_destructor,
	Circle_drawer
};


void *Circle = &CircleClass;
