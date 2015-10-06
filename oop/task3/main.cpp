#include <iostream>

#include "date.h"
#include "calendar.h"


int main(int argc, char **argv)
{
	// TODO: parse input argv.

	Date birthday(1995, 3, 1);
	Date today;

	std::cout << today << " - " << birthday << " = " << today - birthday << std::endl;

	return 0;
}
