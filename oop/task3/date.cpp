#include <time.h>

#include "date.h"


Date::Date()
{
	time_t t = time(NULL);
	struct tm *today = localtime(&t);



	free(today);
}


Date::Date(int year, int month, int day)
	: _year(year), _month(month), _day(day) {}

Date::~Date() {}


std::ostream& operator<<(std::ostream &out, const Date &date)
{
	out << date._day << "." << date._month << "." << date._year;
	return out;
}
