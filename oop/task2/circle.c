#include <stdio.h>
#include <stdlib.h>

#include "class.h"
#include "point.h"
#include "circle.h"


void Circle_initializer(void *_self, StringArray *args)
{
	if ((args == NULL)
			|| (args->m_size < 4))
		return;

	CircleStruct *self = _self;

	self->center = new_object(Point, atoi(sa_get(args, 1)), atoi(sa_get(args, 2)));
	self->radius = atoi(sa_get(args, 3));
}


void Circle_destructor(void *_self)
{
	CircleStruct *self = _self;
	delete_object(self->center);
}


void Circle_drawer(void *_self)
{
	CircleStruct *self = _self;

	print(self->center);
	printf(", r=%d", self->radius);
}


Class CircleClass = {
	sizeof(CircleStruct),
	NULL,
	Circle_initializer,
	Circle_destructor,
	Circle_drawer
};


void *Circle = &CircleClass;
