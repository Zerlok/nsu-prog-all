#include <stdio.h>
#include <stdlib.h>

#include "class.h"
#include "point.h"


void *Point_constructor(void *_self, va_list *args)
{
	PointStruct *self = _self;

	self->x = va_arg(args, int);
	self->y = va_arg(args, int);

	return self;
}


void Point_initializer(void *_self, int argn, char **args)
{
	if ((argn < 2)
			|| (args == NULL))
		return;

	PointStruct *self = _self;

	self->x = atoi(args[0]);
	self->y = atoi(args[1]);
}


void Point_destructor(void *_self) {}


void Point_drawer(void *_self)
{
	PointStruct *self = _self;
	printf("(%d, %d)", self->x, self->y);
}


void move_to(void *ptr_obj, int nx, int ny)
{
	PointStruct *self = ptr_obj;
	self->x = nx;
	self->y = ny;
}


Class PointClass = {
	sizeof(PointStruct),
	Point_constructor,
	Point_initializer,
	Point_destructor,
	Point_drawer
};


void *Point = &PointClass;
