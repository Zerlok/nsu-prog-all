#include <iostream>
#include <vector>
#include "sharedpointer.h"


struct Data
{
	Data(int a, double b, size_t c)
		: x(a), y(b), z(c) {}

	int x;
	double y;
	size_t z;
};


int total()
{
	SharedPointer<Data> p1 = make_shared_pointer(new Data(1, 2.0, 3));
	SharedPointer<Data> p2;
	SharedPointer<Data> p3 = p2;
	SharedPointer<Data> p4;
	SharedPointer<Data> p5(p1);

	p3 = p2 = p1;

	p3 = p4;

	p1.release();

	return 0;
}


int main()
{
	SharedPointer<Data> p;

	std::cout << p.is_null() << std::endl;
	return 0;
}
