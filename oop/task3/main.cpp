#include <iostream>

#include "date.h"


int main(int argc, char **argv)
{
	// parse input argv.

	Date dt(2015, 9, 30);
	std::cout << dt << std::endl;

	return 0;
}

