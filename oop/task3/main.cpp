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

	cf::format() << Date() << std::endl;
	cf::format() << horiz << Calendar(Date(2015, 3, 1), Date()) << std::endl;

	return 0;
}
