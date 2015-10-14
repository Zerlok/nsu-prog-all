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

	cf::format() << cf::vertical << Calendar(2015) << std::endl;

	return 0;
}
