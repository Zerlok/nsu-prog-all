#include <stdio.h>

#include "class.h"
#include "point.h"


void *Point_constructor(void *_self, va_list *args)
{
	PointStruct *self = _self;

	self->x = va_arg(args, int);
	self->y = va_arg(args, int);

	return self;
}


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
	NULL,
	Point_drawer
};


void *Point = &PointClass;
