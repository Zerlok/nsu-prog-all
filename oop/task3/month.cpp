#include <iomanip>

#include "week.h"
#include "month.h"


Month::Month()
{
	Date today;
	_begin = Date(
			today.get_year(),
			today.get_month(),
			1
	);
	_end = get_month_end(today);
}


Month::Month(const Date& date)
{
	_begin = Date(
			date.get_year(),
			date.get_month(),
			1
	);
	_end = get_month_end(date);
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
	_end = get_month_end(_begin);

	return (*this);
}


Month &Month::operator--(int)
{
	_end = _begin - 1;
	_begin = Date(
			_end.get_year(),
			_end.get_month(),
			1
	);

	return (*this);
}


Month Month::operator+(int num)
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


std::string Month::get_header() const
{
	std::ostringstream out;
	const int width = Week::day_width * 7;
	std::string month_name = get_name().substr(0, width);

	const int diff = width - month_name.size();

	if (diff > 0)
	{
		std::string s;
		s.resize((diff/2), ' ');
		s.append(month_name);
		s.resize(width, ' ');
		month_name = s;
	}

	out << std::setfill(' ') << std::setw(width) << month_name << std::endl;
	out << Week::header << std::endl;

	return out.str();
}


const Date &Month::get_month_end(const Date &date) const
{
	Date month_end;

	if (date.get_month() == 12)
		month_end = Date(
				date.get_year() + 1,
				1,
				1
		);

	else
		month_end = Date(
				date.get_year(),
				date.get_month() + 1,
				1
		);

	return month_end--;
}
