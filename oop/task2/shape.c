#include "shape.h"


void *Shape_constructor(void *_self, ...)
{
	printf("Constructor...\n");

	ShapeStruct *self = _self;
	va_list args;
	va_start(args, _self);
	
	self->id = va_arg(args, int);

	va_end(args);
	return self;
}


void Shape_destructor(void *_self)
{
	printf("Destructor...\n");
}


void Shape_printor(void *_self)
{
	printf("[Shape: %d]\n", (*(ShapeStruct**)_self)->id);
}


Class ShapeClass = {
	sizeof(ShapeStruct),
	Shape_constructor,
	Shape_destructor,
	Shape_printor
};


void *Shape = &ShapeClass;
