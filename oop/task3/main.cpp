#include <iostream>

#include "date.h"
#include "week.h"
#include "calendar.h"


int main(int argc, char **argv)
{
	// TODO: parse input argv.

	Date birthday(1995, 3, 1);
	Date today;

	std::cout << today << " - " << birthday << " = " << today - birthday << std::endl;

	std::cout << Week(today) << std::endl;

	return 0;
}
