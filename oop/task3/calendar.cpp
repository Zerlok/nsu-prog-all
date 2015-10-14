#include <iomanip>

#include "week.h"
#include "month.h"
#include "calendar.h"
#include "calendarformat.h"


Calendar::Calendar(const Date &date)
	: _width(3)
{
	Month m = Month(date);
	_begin = m.get_begin();
	_end = m.get_end();
}


Calendar::Calendar(const Date &begin, const Date &end)
	: _width(3)
{
	Month m = Month(begin);
	_begin = m.get_begin();

	if (m.is_contain(end))
		_end = m.get_end();

	else
		_end = Month(end).get_end();
}


Calendar::Calendar(const int year)
	: _begin(year, 1, 1), _end(year, 12, 31), _width(3)
{
}


Calendar::~Calendar()
{
}


std::ostream &operator<<(std::ostream &out, const Calendar &cal)
{
	return out << "<Calendar: " << cal._begin << " - " << cal._end << ">";
}
