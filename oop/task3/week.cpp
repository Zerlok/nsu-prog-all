#include <stdexcept>
#include <sstream>

#include "week.h"


Week::Week(const Date &date)
	: _begin(date), _end(date + 6)
{
	if ((date.get_weekday() > 0)
			&& (date.get_day() > 1)) // is not a first day in month.
	{
		std::ostringstream sstream;
		sstream << "The date is not a " << WEEKDAY_NAMES[0]
				<< " or the begin of month: " << date
				<< " " << date.get_weekday_name().substr(0, 3);
		throw std::invalid_argument(sstream.str());
	}
}


Week::Week(const Date &from, const Date &to)
	: _begin(from), _end(to)
{
	if ((from.get_weekday() > 0)
			&& (from.get_day() > 1))
	{
		std::ostringstream sstream;
		sstream << "The date is not a " << WEEKDAY_NAMES[0]
				<< " or the begin of month: " << from
				<< " " << from.get_weekday_name().substr(0, 3);
		throw std::invalid_argument(sstream.str());
	}

	if ((to.get_weekday() < 6)
			&& ((to+1).get_day() > 1)) // is not the end of month (next day is not the begin of month).
	{
		std::ostringstream sstream;
		sstream << "The date is not a " << WEEKDAY_NAMES[6]
				<< " or the end of month: " << to
				<< " " << to.get_weekday_name().substr(0, 3);
		throw std::invalid_argument(sstream.str());
	}
}
