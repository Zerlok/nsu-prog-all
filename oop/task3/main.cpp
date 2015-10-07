#include <iostream>
#include <sstream>

#include "date.h"
#include "week.h"
#include "calendar.h"


int main(int argc, char **argv)
{
	// TODO: parse input argv.

	Date birthday(1995, 3, 1);
	Date today;

	std::cout << today << " - " << birthday << " = " << today - birthday << std::endl;

	std::ostringstream ostr;
	Week week(Date(2015, 10, 1));
	ostr << Week::weekday_names << std::endl << week << std::endl;
	ostr << week++ << std::endl;
	ostr << week++ << std::endl;
	ostr << week++ << std::endl;
	ostr << week++ << std::endl;
	ostr << week++ << std::endl;
	ostr << week++ << std::endl;
	std::cout << ostr.str();

	return 0;
}
