#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__


#include <stdarg.h>
#include "extrastring.h"


typedef struct _Rectangle
{
	Class *super;

	void *begin;
	void *end;
} RectangleStruct;


void Rectangle_initializer(void *_self, String *args);
void Rectangle_destructor(void *_self);
void Rectangle_drawer(void *_self);


extern void *Rectangle;


// __RECTANGLE_H__
#endif
