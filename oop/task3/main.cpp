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

	 std::cout << cf::vertical << Calendar(Date(2015, 3, 1), Date(2015, 11, 1)) << std::endl;

	return 0;
}
