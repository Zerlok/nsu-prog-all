#include <iostream>
#include <sstream>

#include "date.h"
#include "week.h"
#include "month.h"
#include "calendar.h"


int main(int argc, char **argv)
{
	// TODO: parse input argv.

	Date birthday(1995, 3, 1);
	Date today;

	std::cout << today << " - " << birthday << " = " << today - birthday << std::endl;

	Month month;
	std::cout << month.get_header() << month << std::endl;
	month++;
	std::cout << month.get_header() << month << std::endl;
	month++;
	std::cout << month.get_header();
	std::cout << month << std::endl;
	month++;
	std::cout << month.get_header() << month << std::endl;

	return 0;
}
