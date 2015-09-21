#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "class.h"
#include "shape.h"


void *Shape_constructor(void *_self, va_list *args)
{
	ShapeStruct *self = _self;

	char *name = va_arg(*args, char*);
	size_t name_len = strlen(name);
	self->name = (char*)calloc(name_len + 1, sizeof(char));
	memcpy(self->name, name, name_len);

	self->drawer = Shape_drawer;

	return self;
}


void Shape_destructor(void *_self)
{
	ShapeStruct *self = _self;
	free(self->name);
}


void Shape_drawer(void *_self)
{
	ShapeStruct *self = _self;
	printf("[Shape: '%s']\n", self->name);
}


void draw(void *ptr_obj)
{
	ShapeStruct *obj = ptr_obj;
	obj->drawer(ptr_obj);
}


Class ShapeClass = {
	sizeof(ShapeStruct),
	Shape_constructor,
	Shape_destructor,
	Shape_printor
};


void *Shape = &ShapeClass;
