#include <time.h>
#include <iomanip>
#include <sstream>
#include <stdexcept>

#include "date.h"


const int Date::TM_STRUCT_ZERO_YEAR = 1900;


Date Date::create_year_begin(int year)
{
	return Date(year, 1, 1);
}


Date Date::create_year_end(int year)
{
	return Date(year, MONTHS_IN_YEAR_NUM, DAYS_IN_MONTH[MONTHS_IN_YEAR_NUM-1]);
}


Date Date::create_month_begin(int year, int month)
{
	int m = ((MONTHS_IN_YEAR_NUM + month - 1) % MONTHS_IN_YEAR_NUM) + 1;
	return Date(year, m, 1);
}


Date Date::create_month_end(int year, int month)
{
	int m = ((MONTHS_IN_YEAR_NUM + month - 1) % MONTHS_IN_YEAR_NUM) + 1;
	Date d =Date(year, m, DAYS_IN_MONTH[m-1]);

	if ((m == 2)
			&& d.is_leap_year())
		d++;

	return d;
}


Date::Date()
{
	time_t t = time(NULL);
	struct tm *today = localtime(&t);

	_year = today->tm_year + Date::TM_STRUCT_ZERO_YEAR;
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
	++_month;

	if (_month <= MONTHS_IN_YEAR_NUM)
		return (*this);

	_month = 1;
	++_year;
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


Date Date::operator+(int days) const
{
	if (days < 0)
		return this->operator-(-days);

	Date d = Date(*this);
	for (int i = 0; i < days; i++)
		d++;

	return d;
}


Date Date::operator-(int days) const
{
	if (days < 0)
		return this->operator+(-days);

	Date d = Date(*this);
	for (int i = 0; i < days; i++)
		d--;

	return d;
}


long long int operator-(const Date &date1, const Date &date2)
{
	return (date1._days_num - date2._days_num);
}


std::ostream &operator<<(std::ostream &out, const Date &date)
{
	out << std::setfill('0')
		<< std::setw(2) << date._day << "."
		<< std::setw(2) << date._month << "."
		<< std::setw(4) << date._year;

	return out;
}


bool Date::is_leap_year() const
{
	return (((_year % 4 == 0)
				&& (_year % 100 != 0))
			|| (_year % 400 == 0)
	);
}


bool Date::is_valid() const
{
	return ((_day > 0)
			&& (_day <= get_days_in_month())
			&& (_month > 0)
			&& (_month <= MONTHS_IN_YEAR_NUM)
	);
}


long long int Date::count_days() const
{
	int year = _year - 1;
	long long int total = (year * DAYS_IN_YEAR_NUM) + (year / 4) - (year / 100) + (year / 400);

	for (int i = 1; i < _month; i++)
		total += get_days_in_month(-i);

	total += (_day - 1);
	return total;
}


int Date::get_days_in_month(int diff) const
{
	int i = (11 + _month + diff) % MONTHS_IN_YEAR_NUM;

	if ((i == 1)
			&& (is_leap_year()))
		return DAYS_IN_MONTH[i] + 1;

	return DAYS_IN_MONTH[i];
}
