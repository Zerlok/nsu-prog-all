#include <iostream>
#include <vector>
#include "haartransformation.h"


template<class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec)
{
	std::cout << '{';
	for (const T& v : vec)
		std::cout << v << ' ';
	std::cout << '}' << std::endl;

	return out;
}


std::ostream& operator<<(std::ostream& out, const typename std::vector<int>::iterator& it)
{
	return out << (*it) << ": " << &(*it);
}


int main(int argc, char *argv[])
{
	std::cout << "Hello World!" << std::endl;

	Floats vec = {10.0, 12.0, 5.6, 4.2, 3.2, 5.9, 10.2, -2.0, -3.0, -2.7};
	std::cout << vec << std::endl;

	HaarTransformation ht;
	ht.forward(vec);
	std::cout << vec << std::endl;

	ht.backward(vec);
	std::cout << vec << std::endl;

	return 0;
}

