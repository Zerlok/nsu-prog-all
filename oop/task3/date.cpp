#include <time.h>
#include <stdexcept>
#include <sstream>

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
	if (!is_valid())
	{
		std::ostringstream sstream;
		sstream << "Invalid date: " << (*this);
		throw std::invalid_argument(sstream.str());
	}
}


Date::~Date()
{

}


Date &Date::operator++(int)
{
	++_day;

	if (_day <= get_days_in_month())
		return (*this);

	add_month();
	return (*this);
}


Date &Date::operator--(int)
{
	--_day;

	if (_day > 0)
		return (*this);

	sub_month();
	return (*this);
}


Date &operator+(Date &date, int days)
{
	Date d(date);
	for (int i = 0; i < days; i++)
		d++;

	return d;
}


Date &operator-(const Date &date, int days)
{
	Date d(date);
	for (int i = 0; i < days; i++)
		d--;

	return d;
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

	for (int i = 1; i < _month; i++)
		total += get_days_in_month(-i);

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


int Date::get_weekday_num() const
{
	return count_days() % 7;
}


const std::string &Date::get_weekday() const
{
	return WEEK_DAYS[get_weekday_num()];
}


void Date::add_week()
{
	int max_day = get_days_in_month();
	_day += 7;

	if (_day <= max_day)
		return;

	_day -= max_day;
	add_month();
}


void Date::add_month()
{
	++_month;

	if (_month <= 12)
		return;

	_month = 1;
	++_year;
}


void Date::sub_week()
{
	_day -= 7;

	if (_day > 0)
		return;

	_day += get_days_in_month(-1);
	sub_month();
}


void Date::sub_month()
{
	--_month;

	if (_month > 0)
		return;

	_month = 12;
	--_year;
}


bool Date::is_valid() const
{
	return ((_day > 0)
			&& (_day <= get_days_in_month())
			&& (_month > 0)
			&& (_month <= 12)
	);
}


int Date::get_days_in_month(int diff) const
{
	int month = (_month + diff) % 12;

	if ((month == 2)
			&& (is_leap_year()))
		return DAYS_IN_MONTH[month-1] + 1;

	return DAYS_IN_MONTH[month-1];
}
