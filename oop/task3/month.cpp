#include <iomanip>

#include "week.h"
#include "month.h"


Month::Month()
{
	Date today;
	_begin = Date::create_month_begin(today.get_year(), today.get_month());
	_end = Date::create_month_end(today.get_year(), today.get_month());
}


Month::Month(const Date& date)
{
	_begin = Date::create_month_begin(date.get_year(), date.get_month());
	_end = Date::create_month_end(date.get_year(), date.get_month());
}


Month::Month(const Month &month)
{
	_begin = month._begin;
	_end = month._end;
}


Month &Month::operator=(const Month &month)
{
	_begin = month._begin;
	_end = month._end;

	return (*this);
}


Month &Month::operator++(int)
{
	_begin = _end + 1;
	_end = Date::create_month_end(_begin.get_year(), _begin.get_month());

	return (*this);
}


Month &Month::operator--(int)
{
	_end = _begin - 1;
	_begin = Date::create_month_begin(_end.get_year(), _end.get_month());

	return (*this);
}


Month Month::operator+(int num) const
{
	Month m(*this);
	for (int i = 0; i < num; i++)
		m++;

	return m;
}


Month &Month::operator+=(int num)
{
	for (int i = 0; i < num; i++)
		(*this)++;

	return (*this);
}


std::ostream &operator<<(std::ostream &out, const Month &month)
{
	return out << "<Month: " << month._begin << " - " << month._end << ">";
}
