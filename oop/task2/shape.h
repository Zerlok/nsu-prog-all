#ifndef __SHAPE_H__
#define __SHAPE_H__


#include <stdarg.h>


typedef struct _Shape
{
	Class cls;

	char *name;

	void (*drawer)(void *_self);
} ShapeStruct;


void *Shape_constructor(void *_self, va_list *args);
void Shape_destructor(void *_self);
void Shape_printor(void *_self);
void Shape_drawer(void *_self);

void draw(void *ptr_obj);


extern void *Shape;


// __SHAPE_H__
#endif
