#include <iostream>

#include "date.h"


int main(int argc, char **argv)
{
	// TODO: parse input argv.

	Date date1(2015, 9, 30);
	Date date2(1995, 3, 1);

	std::cout << date1 << " - " << date2 << " = " << date1 - date2 << std::endl;

	return 0;
}

