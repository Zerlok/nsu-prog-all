#ifndef __POINT_H__
#define __POINT_H__


#include <stdarg.h>
#include "extrastring.h"


typedef struct _Point
{
	Class *super;

	int x;
	int y;
} PointStruct;


void *Point_constructor(void *_self, va_list *args);
void Point_initializer(void *_self, String *args);
void Point_drawer(void *_self);

void move_to(void *ptr_obj, int nx, int ny);


extern void *Point;


// __POINT_H__
#endif
