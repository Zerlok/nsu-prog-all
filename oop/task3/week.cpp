#include <stdexcept>
#include <sstream>
#include <iomanip>

#include "week.h"


Week::Week()
	: _begin(), _end()
{
	if ((_begin.get_day() > 1)
			  && (_begin.get_weekday() > 0))
		_begin = _begin - _begin.get_weekday();

	_end = _begin + (DAYS_IN_WEEK_NUM - _begin.get_weekday() - 1);

	while ((_end.get_month() > _begin.get_month())
		   || (_end.get_year() > _begin.get_year()))
		_end--;
}


Week::Week(const Date &date)
	: _begin(date), _end(date)
{
	if (_begin.get_weekday() > _begin.get_day() - 1)
		_begin = _begin - (_begin.get_day() - 1);

	else if ((_begin.get_day() > 1)
			&& (_begin.get_weekday() > 0))
		_begin = _begin - _begin.get_weekday();

	_end = _begin + (DAYS_IN_WEEK_NUM - _begin.get_weekday() - 1);

	while ((_end.get_month() > _begin.get_month())
		   || (_end.get_year() > _begin.get_year()))
		_end--;
}


Week::Week(const Date &from, const Date &to)
	: _begin(from), _end(to)
{
	if (to < from)
	{
		std::ostringstream sstream;
		sstream << "The end date is less than begin: " << to << " < " << from;
		throw std::invalid_argument(sstream.str());
	}

	if ((from.get_weekday() > 0)
			&& (from.get_day() > 1))
	{
		std::ostringstream sstream;
		sstream << "The date is not a " << WEEKDAY_NAMES[0]
				<< " or the begin of month: " << from
				<< " " << from.get_weekday_name().substr(0, 3);
		throw std::invalid_argument(sstream.str());
	}

	if ((to.get_weekday() < DAYS_IN_WEEK_NUM - 1)
			&& ((to+1).get_day() > 1)) // is not the end of month (next day is not the begin of month).
	{
		std::ostringstream sstream;
		sstream << "The date is not a " << WEEKDAY_NAMES[DAYS_IN_WEEK_NUM - 1]
				<< " or the end of month: " << to
				<< " " << to.get_weekday_name().substr(0, 3);
		throw std::invalid_argument(sstream.str());
	}
}


Week::Week(const Week &week)
	: _begin(week._begin), _end(week._end)
{
}


Week::~Week()
{
}


Week &Week::operator=(const Week &week)
{
	_begin = week._begin;
	_end = week._end;

	return (*this);
}


Week &Week::operator++(int)
{
	_begin = _end + 1;
	_end = _begin + (DAYS_IN_WEEK_NUM - _begin.get_weekday() - 1);

	while (_end.get_month() != _begin.get_month())
		_end--;

	return (*this);
}


Week &Week::operator--(int)
{
	_end = _begin - 1;
	_begin = _end - _end.get_weekday();

	while (_begin.get_month() < _end.get_month())
		_begin++;

	return (*this);
}


Week Week::operator+(int n) const
{
	Week w(*this);

	for (int i = 0; i < n; i++)
		w++;

	return w;
}


std::ostream &operator<<(std::ostream &out, const Week &week)
{
	return out << "<Week: " << week._begin << " - " << week._end << ">";
}
