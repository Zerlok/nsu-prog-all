#include <iostream>
#include "pool.h"


int main()
{
	Pool<int, 10> ints;

	int& i = ints.create(100);

	for (int i = 1; i < 10; ++i)
		std::cout << ints.create(i) << std::endl;

	ints.clear(i);

	std::cout << ints.create(10) << std::endl;

	return 0;
}
