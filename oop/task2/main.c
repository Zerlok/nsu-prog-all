#include "class.h"
#include "shape.h"
#include "point.h"


int main(int argc, char **argv)
{
	void *s = new_object(Shape, "asdfg");
	void *u = new_object(Shape, "hello");
	void *dot = new_object(Point, 10, 11);

	ShapeStruct *ss = s;
	ShapeStruct *uu = u;
	ShapeStruct *dd = dot;
	PointStruct *ddd = dot;

	draw(s);
	draw(u);
	draw(dot);

	delete_object(s);
	delete_object(u);
	delete_object(dot);

	return 0;
}
