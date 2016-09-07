#include <iostream>
#include <vector>
#include "pool.h"


int main()
{
	Pool<std::vector<int>, 5> ints;

	std::vector<int> &vec = ints.create({0, 1, 1, 2});

	for (auto i : vec)
		std::cout << i << std::endl;

	return 0;
}
