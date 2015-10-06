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
	_days_num = count_days();
}


Date::Date(const Date &date)
	: _year(date._year), _month(date._month), _day(date._day)
{
	_days_num = count_days();
}


Date::Date(int year, int month, int day)
	: _year(year), _month(month), _day(day), _days_num(0)
{
	if (!is_valid())
	{
		std::ostringstream sstream;
		sstream << "Invalid date: " << (*this);
		throw std::invalid_argument(sstream.str());
	}

	_days_num = count_days();
}


Date::~Date()
{
}


Date &Date::operator=(const Date &date)
{
	_days_num = date._days_num;
	_day = date._day;
	_month = date._month;
	_year = date._year;

	return (*this);
}


Date &Date::operator++(int)
{
	++_days_num;
	++_day;

	if (_day <= get_days_in_month())
		return (*this);

	_day = 1;
	add_month();
	return (*this);
}


Date &Date::operator--(int)
{
	--_days_num;
	--_day;

	if (_day > 0)
		return (*this);

	_day = get_days_in_month(-1);
	--_month;

	if (_month > 0)
		return (*this);

	_month = 12;
	--_year;
	return (*this);
}


Date &operator+(Date &date, int days)
{
	Date *d = new Date(date);
	for (int i = 0; i < days; i++)
		(*d)++;

	return (*d);
}


Date &operator-(const Date &date, int days)
{
	Date *d = new Date(date);
	for (int i = 0; i < days; i++)
		(*d)--;

	return (*d);
}


long long int operator-(const Date &date1, const Date &date2)
{
	return (date1._days_num - date2._days_num);
}


std::ostream &operator<<(std::ostream &out, const Date &date)
{
	out << date._day << "." << date._month << "." << date._year;
	return out;
}


bool Date::is_leap_year() const
{
	return (((_year % 4 == 0)
				&& (_year % 100 != 0))
			|| (_year % 400 == 0)
	);
}


void Date::add_week()
{
	_days_num += 7;

	int max_day = get_days_in_month();
	_day += 7;

	if (_day <= max_day)
		return;

	_day -= max_day;
	++_month;

	if (_month <= 12)
		return;

	_month = 1;
	++_year;
}


void Date::add_month()
{
	_days_num += get_days_in_month();
	++_month;

	if (_month <= 12)
		return;

	_month = 1;
	++_year;
}


void Date::sub_week()
{
	_days_num -= 7;
	_day -= 7;

	if (_day > 0)
		return;

	_day += get_days_in_month(-1);
	--_month;

	if (_month > 0)
		return;

	_month = 12;
	--_year;
}


void Date::sub_month()
{
	//   Feb     |			  Mar          |    Apr
	//         .---<------<-------,--,--,
	// ... 27 28 | 01 02 ... 28 (29 30 31) | 01 ...
	//      ^----------------^
	int month_max_days = get_days_in_month(-1);
	_days_num -= month_max_days;
	--_month;

	if (_month > 0)
		return;

	_month = 12;
	--_year;

	if (_day > month_max_days)
	{
		_days_num -= (_day - month_max_days);
		_day = month_max_days;
	}
}


bool Date::is_valid() const
{
	return ((_day > 0)
			&& (_day <= get_days_in_month())
			&& (_month > 0)
			&& (_month <= 12)
	);
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


int Date::get_days_in_month(int diff) const
{
	int i = (_month-1 + diff) % 12;

	if ((i == 1)
			&& (is_leap_year()))
		return DAYS_IN_MONTH[i] + 1;

	return DAYS_IN_MONTH[i];
}
