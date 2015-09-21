#include "class.h"
#include "shape.h"
#include "point.h"


void *Point_constructor(void *_self, va_list *args)
{
	PointStruct *self = _self;
	// Firstly - create parent object.
	self->parent = new_object(Shape, "Point");
	self->parent->drawer = Point_drawer;

	self->x = va_arg(args, int);
	self->y = va_arg(args, int);

	return self;
}


void Point_destructor(void *_self)
{
	PointStruct *self = _self;

	// At the end - remove parent object.
	delete_object(self->parent);
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
	Point_destructor
};


void *Point = &PointClass;
