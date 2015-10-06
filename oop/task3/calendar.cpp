#include "calendar.h"


Calendar::Calendar(const Date &begin, const Date &end, const CalendarFormat &format)
	: _begin(begin), _end(end), _format(format)
{
}


Calendar::Calendar(const int year, const CalendarFormat &format)
	: _begin(year, 1, 1), _end(year+1, 12, 31), _format(format)
{
}


Calendar::~Calendar()
{
}


std::ostream &operator<<(std::ostream &out, const Calendar &cal)
{
	out << std::setfill(' ');
	out << std::setw(28) << cal._begin.get_month_name() << std::endl;

	for (int i = 0; i < 7; i++)
		out << std::setw(4) << WEEKDAY_NAMES[i].substr(0, 3);
	out << std::endl;

	for (int i = 0; i < cal._begin.get_weekday(); i++)
		out << std::setw(4) << ".";

	Date date(cal._begin);
	Date week_end(
			date.get_year(),
			date.get_month(),
			8 - date.get_weekday() // add_week() here.
	);
	Date month_end(cal._end);
//	month_end.add_month();

	while (week_end <= month_end)
	{
		while (date < week_end)
		{
			out << std::setw(4) << date.get_day();
			date++;
		}

		out << std::endl;

		if (week_end < month_end)
			week_end.add_week();

		if (week_end > month_end)
			week_end = month_end;
	}

	out << std::endl;

	return out;
}


void Calendar::set_format(const CalendarFormat &format)
{
}
