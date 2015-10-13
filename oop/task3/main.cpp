#include <iostream>
#include <sstream>

#include "date.h"
#include "week.h"
#include "month.h"
#include "calendar.h"
#include "calendarformat.h"


int main(int argc, char **argv)
{
	// TODO: parse input argv.

//	std::cout << init_format << display_day << Date() << std::endl;
	std::cout << init_format << Month(Date(2015, 1, 1)) << std::endl;

	return 0;
}
