#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__


#include <stdarg.h>


typedef struct _Rectangle
{
	Class cls;

	void *begin;
	void *end;
} RectangleStruct;


void *Rectangle_constructor(void *_self, va_list *args);
void Rectangle_destructor(void *_self);
void Rectangle_drawer(void *_self);


extern void *Rectangle;


// __RECTANGLE_H__
#endif
