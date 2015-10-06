#include <iostream>

#include "date.h"
#include "calendar.h"
#include "calendarformat.h"


int main(int argc, char **argv)
{
	// TODO: parse input argv.

	Date date2(1996, 6, 18);
	Date date1(1995, 3, 1);

	std::cout << date2 << " - " << date1 << " = " << date2 - date1 << std::endl;

	Calendar cal(Date(2015, 10, 1), Date(2015, 11, 1), CalendarFormat(std::string("")));

	std::cout << cal << std::endl;

	return 0;
}
