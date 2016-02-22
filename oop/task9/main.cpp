#include <iostream>
#include <vector>
#include "heapsort.h"


int main()
{
	std::vector<int> values = {1, 0, 0, 1, 1, 0, 0, 1, 0};

	for (int& x : values)
		std::cout << x << " ";
	std::cout << std::endl;

	heap_sort(values);

	for (int& x : values)
		std::cout << x << " ";
	std::cout << std::endl;

	return 0;
}
