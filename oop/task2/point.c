#include <stdio.h>
#include <stdlib.h>

#include "class.h"
#include "point.h"


void *Point_constructor(void *_self, va_list *args)
{
	PointStruct *self = _self;

	self->x = va_arg(args, int);
	self->y = va_arg(args, int);
}


void Point_initializer(void *_self, String *args)
{
	PointStruct *self = _self;

	self->x = atoi(str_get(args, 1));
	self->y = atoi(str_get(args, 2));
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
	NULL,
	Point_initializer,
	NULL,
	Point_drawer
};


void *Point = &PointClass;
