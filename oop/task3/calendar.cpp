#include <iomanip>

#include "week.h"
#include "month.h"
#include "calendar.h"
#include "calendarformat.h"


Calendar::Calendar(const Date &begin, const Date &end)
	: _begin(begin), _end(end), _width(3)
{
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
