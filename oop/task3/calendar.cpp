#include "calendar.h"


Calendar::Calendar(const Date &begin, const Date &end)
	: _begin(begin), _end(end)
{
}


Calendar::Calendar(const int year)
	: _begin(year, 1, 1), _end(year+1, 12, 31)
{
}


Calendar::~Calendar()
{
}


std::ostream &operator<<(std::ostream &out, const Calendar &cal)
{
	return out;
}
