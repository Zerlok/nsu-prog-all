#include <iomanip>

#include "week.h"
#include "month.h"
#include "calendar.h"
#include "calendarformat.h"


const int Calendar::DEFAULT_WIDTH = 3;


Calendar::Calendar()
	: _width(Calendar::DEFAULT_WIDTH)
{
	Date today;
	_begin = Date::create_month_begin(today.get_year(), today.get_month());
	_end = Date::create_month_end(today.get_year(), today.get_month());
}


Calendar::Calendar(const Date &date)
	: _width(Calendar::DEFAULT_WIDTH)
{
	Month m = Month(date);
	_begin = m.get_begin();
	_end = m.get_end();
}


Calendar::Calendar(const Date &begin, const Date &end)
	: _width(Calendar::DEFAULT_WIDTH)
{
	Month m(begin);
	_begin = m.get_begin();

	if (m.is_contain(end))
		_end = m.get_end();

	else
		_end = Date::create_month_end(end.get_year(), end.get_month());
}


Calendar::Calendar(const int year)
	: _begin(Date::create_year_begin(year)),
	  _end(Date::create_year_end(year)),
	  _width(Calendar::DEFAULT_WIDTH)
{
}


Calendar::~Calendar()
{
}


std::ostream &operator<<(std::ostream &out, const Calendar &cal)
{
	return out << "<Calendar: " << cal._begin << " - " << cal._end << ">";
}
