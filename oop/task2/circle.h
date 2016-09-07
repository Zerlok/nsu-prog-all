#ifndef __CIRCLE_H__
#define __CIRCLE_H__


#include <stdarg.h>
#include "extrastring.h"


typedef struct _Circle
{
	Class *super;

	void *center;
	int radius;
} CircleStruct;


void *Circle_constructor(void *_self, va_list *args);
void Circle_initializer(void *_self, int argn, char **args);
void Circle_destructor(void *_self);
void Circle_drawer(void *_self);


extern void *Circle;


// __CIRCLE_H__
#endif
