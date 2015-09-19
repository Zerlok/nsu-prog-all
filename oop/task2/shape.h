#ifndef __SHAPE_H__
#define __SHAPE_H__


typedef struct _Shape
{
	Class super;

	int id;
} ShapeStruct;


void *Shape_constructor(void *_self, va_list *args);
void Shape_destructor(void *_self);
void Shape_printor(void *_self);


extern const void *Shape;


// __SHAPE_H__
#endif
