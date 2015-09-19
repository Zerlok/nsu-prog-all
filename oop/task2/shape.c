#include "shape.h"


void *Shape_constructor(void *_self, va_list *args)
{
	printf("Constructor...\n");

	ShapeStruct *self = _self;
	self->id = va_list(args, int);

	return self;
}


void Shape_destructor(void *_self)
{
	printf("Destructor...\n");
}


void Shape_printor(void *_self)
{
	printf("[Shape: %s]\n", (*(ShapeStruct**)_self)->id);
}


const Class ShapeClass = {
	sizeof(ShapeStruct),
	Shape_constructor,
	Shape_destructor,
	Shape_printor
};


void *Shape = &ShapeClass;
