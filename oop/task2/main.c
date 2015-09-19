#include "class.h"
#include "shape.h"


int main(int argc, char **argv)
{
	void *s = new(Shape, 12);
	void *u = new(Shape, 13);

	print(s);
	print(u);

	delete(s);
	delete(u);

	return 0;
}
