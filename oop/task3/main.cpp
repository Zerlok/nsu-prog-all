#include <iostream>

#include "date.h"


int main(int argc, char **argv)
{
	// TODO: parse input argv.

	Date date1;
	Date date2(1995, 3, 1);

	std::cout << date1 << " - " << date2 << " = " << date1 - date2 << std::endl;

	std::cout << date1.get_weekday() << std::endl;
	std::cout << date1++ << std::endl;

	date1.add_week();
	std::cout << date1 << std::endl;

	date1.add_week();
	std::cout << date1 << std::endl;

	date1.add_week();
	std::cout << date1 << std::endl;

	date1.add_week();
	std::cout << date1 << std::endl;

	date1.add_week();
	std::cout << date1 << std::endl;

	date1.add_month();
	std::cout << date1 << std::endl;

	date1.add_month();
	std::cout << date1 << std::endl;

	date2 = date1 - 5;
	date1.add_week();
	std::cout << date1 - date2 << std::endl;

	return 0;
}

