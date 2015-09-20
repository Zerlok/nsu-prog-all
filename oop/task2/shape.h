#ifndef __SHAPE_H__
#define __SHAPE_H__


#include <stdio.h>
#include <stdarg.h>

#include "class.h"


typedef struct _Shape
{
	Class super;

	int id;
} ShapeStruct;


void *Shape_constructor(void *_self, ...);
void Shape_destructor(void *_self);
void Shape_printor(void *_self);


extern void *Shape;


// __SHAPE_H__
#endif
