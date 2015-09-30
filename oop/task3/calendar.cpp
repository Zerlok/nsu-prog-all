#include "calendar.h"


Calendar::Calendar(const Date &begin, const CalendarFormat &format)
	: _begin(begin), _end(begin), _format(format)
{
}


Calendar::Calendar(const Date &begin, const Date &end, const CalendarFormat &format)
	: _begin(begin), _end(end), _format(format)
{
}


Calendar::Calendar(const int year, const CalendarFormat &format)
	: _format(format)
{
	_begin = Date(year);
	_end = Date(year + 1);
}


std::ostream& operator<<(std::iostream &out, Calendar &cal)
{
	return out;
}
