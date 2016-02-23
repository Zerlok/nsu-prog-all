#include <iostream>
#include <vector>
#include "sharedpointer.h"


struct Checker
{
	Checker(int a, double b, size_t c)
		: x(a), y(b), z(c) {}

	int x;
	double y;
	size_t z;
};


int total()
{
	SharedPointer<Checker> p1 = make_shared_pointer(new Checker(1, 2.0, 3));
	SharedPointer<Checker> p2;
	SharedPointer<Checker> p3 = p2;
	SharedPointer<Checker> p4;
	SharedPointer<Checker> p5(p1);

	p3 = p2 = p1;

	p3 = p4;

	p1.release();

	return 0;
}


int main()
{
	SharedPointer<Checker> p;

	std::cout << p.is_null() << std::endl;
	return 0;
}
