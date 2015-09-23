#include <stdio.h>

#include "class.h"
#include "point.h"
#include "circle.h"
#include "rectangle.h"


int main(int argc, char **argv)
{
	void *dot = new_object(Point, 10, 11);
	void *rect = new_object(Rectangle, 0, 0, 3, 5);
	void *circ = new_object(Circle, 1, 1, 4);

	print(dot);
	printf("\n");
	print(rect);
	printf("\n");
	print(circ);
	printf("\n");

	delete_object(dot);
	delete_object(rect);
	delete_object(circ);

	return 0;
}
