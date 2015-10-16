#include <iostream>
#include <sstream>

#include "date.h"
#include "week.h"
#include "month.h"
#include "calendar.h"
#include "calendarformat.h"
#include "calendarparser.h"


int main(int argc, char **argv)
{
	CalendarParser parser(argc, argv);

	parser.get_calendar_format() << Calendar(parser.get_calendar_begin(), parser.get_calendar_end()) << std::endl;

	return 0;
}
