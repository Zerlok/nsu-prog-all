#ifndef __POINT_H__
#define __POINT_H__


#include <stdarg.h>


typedef struct _Point
{
	Class cls;
	ShapeStruct *parent;

	int x;
	int y;
} PointStruct;


void *Point_constructor(void *_self, va_list *args);
void Point_destructor(void *_self);
void Point_drawer(void *_self);

void move_to(void *ptr_obj, int nx, int ny);


extern void *Point;


// __POINT_H__
#endif
