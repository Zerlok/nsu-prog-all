#include <time.h>

#include "date.h"


Date::Date()
{
	time_t t = time(NULL);
	struct tm *today = localtime(&t);

	_year = today->tm_year + 1900;
	_month = today->tm_mon + 1;
	_day = today->tm_mday;
}


Date::Date(int year, int month, int day)
	: _year(year), _month(month), _day(day)
{

}


Date::~Date()
{

}


long long int operator-(const Date &date1, const Date &date2)
{
	return date1.count_days() - date2.count_days();
}


std::ostream& operator<<(std::ostream &out, const Date &date)
{
	out << date._day << "." << date._month << "." << date._year;
	return out;
}


long long int Date::count_days() const
{
	int year = _year - 1;
	long long int total = (year * 365) + (year / 4) - (year / 100) + (year / 400);

	for (int i = _month-1; i > 0; i--)
	{
		total += DAYS_IN_MONTH[i-1];

		if ((i == 2)
				&& (is_leap_year()))
			total += 1;
	}

	total += (_day - 1);
	return total;
}


bool Date::is_leap_year() const
{
	return (((_year % 4 == 0)
				&& (_year % 100 != 0))
			|| (_year % 400 == 0)
	);
}
