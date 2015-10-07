#include <stdexcept>
#include <sstream>
#include <iomanip>

#include "week.h"


std::ostream &Week::header(std::ostream &out)
{
	for (int i = 0; i < 7; i++)
		out << std::setfill(' ') << std::setw(Week::day_width)
			<< WEEKDAY_NAMES[i].substr(0, Week::day_width-1);

	return out;
}


Week::Week()
	: _begin(), _end()
{
	if ((_begin.get_day() > 1)
			  && (_begin.get_weekday() > 0))
		_begin = _begin - _begin.get_weekday();

	_end = _begin + (6 - _begin.get_weekday());

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

	_end = _begin + (6 - _begin.get_weekday());

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
	_end = _begin + (6 - _begin.get_weekday());

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


std::ostream &operator<<(std::ostream &out, const Week &week)
{
	for (int i = 0; i < week._begin.get_weekday(); i++)
		out << std::setfill(' ') << std::setw(Week::day_width) << " ";

	for (Date d = week._begin; d <= week._end; d++)
		out << std::setfill(' ') << std::setw(Week::day_width) << d.get_day();

	for (int i = week._end.get_weekday() + 1; i < 7; i++)
		out << std::setfill(' ') << std::setw(Week::day_width) <<	" ";

	return out;
}
