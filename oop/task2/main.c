#include "class.h"
#include "shape.h"


int main(int argc, char **argv)
{
	void *s = new(Shape, "asdfg");
	void *u = new(Shape, "hello");

	print(s);
	print(u);

	delete(s);
	delete(u);

	return 0;
}
