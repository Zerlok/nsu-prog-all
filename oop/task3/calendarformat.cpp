#include <iomanip>
#include <string>
#include <sstream>

#include "calendarformat.h"


const char CalendarFormat::SPACE_SYMBOL = ' ';


CalendarFormat init_format(std::ostream &out)
{
	return CalendarFormat(out);
}

CalendarFormat operator<<(std::ostream &out, CalendarFormat (*func)(std::ostream&))
{
	return func(out);
}


CalendarFormat &display_day(CalendarFormat &format)
{
	format._day_display = true;
	format._out << std::setfill(format._space_symbol) << std::setw(format._day_width);

	return format;
}


CalendarFormat &display_month_name(CalendarFormat &format)
{
	format._month_name_display = true;
	format._out << std::setfill(format._space_symbol) << std::setw(format._week_width);

	return format;
}


CalendarFormat &display_week_header(CalendarFormat &format)
{
	format._out << std::setfill(format._space_symbol);

	for (int i = 0; i < 7; i++)
		format._out << std::setw(format._day_width)
			<< WEEKDAY_NAMES[i].substr(0, format._day_width - 1);

	return format;
}


CalendarFormat &empty_week_fill(CalendarFormat &format)
{
	format._out << std::setfill(format._space_symbol);

	for (int i = 0; i < 7; i++)
		format._out << std::setw(format._day_width) << format._space_symbol;

	return format;
}


CalendarFormat &fill_week_begin(CalendarFormat &format)
{
	format._week_begin_fill = true;
	format._out << std::setfill(format._space_symbol);

	return format;
}


CalendarFormat &fill_week_end(CalendarFormat &format)
{
	format._week_end_fill = true;
	format._out << std::setfill(format._space_symbol);

	return format;
}


CalendarFormat::CalendarFormat()
	: _out(std::cout)
{
	init();
}


CalendarFormat::CalendarFormat(std::ostream &out)
	: _out(out)
{
	init();
}


void CalendarFormat::init()
{
	turn_flags_false();
	_space_symbol		= CalendarFormat::SPACE_SYMBOL;
	_day_width			= 3;
	_week_width			= _day_width * 7;
}


void CalendarFormat::turn_flags_false()
{
	_day_display		= false;
	_month_name_display	= false;
	_week_begin_fill	= false;
	_week_end_fill		= false;
}


CalendarFormat::~CalendarFormat()
{
	_out << std::endl;
}


CalendarFormat &CalendarFormat::operator<<(const Date &date)
{
	if (_day_display)
		_out << date.get_day();

	else if (_month_name_display)
		_out << date.get_month_name();

	else if (_week_begin_fill)
		for (int i = 0; i < date.get_weekday(); i++)
			_out << std::setw(_day_width) << _space_symbol;

	else if (_week_end_fill)
		for (int i = date.get_weekday(); i < 6; i++)
			_out << std::setw(_day_width) << _space_symbol;

	else
		_out << date;

	turn_flags_false();

	return (*this);
}


CalendarFormat &CalendarFormat::operator<<(const Week &week)
{
	return (*this);
}


CalendarFormat &CalendarFormat::operator<<(const Month &month)
{
	// Display month name.
	if (_month_name_display)
	{
		(*this) << month.get_begin();
		return (*this);
	}

	(*this) << display_month_name << month << std::endl;

	// Display names of days in the week.
	_out << std::right;
	(*this) << display_week_header << std::endl;

	// Display by each week of each month in line.
	for (Week week = Week(month.get_begin()); week <= month.get_end(); week++)
	{
		if (week.get_begin() <= month.get_end())
		{
			(*this) << fill_week_begin << week.get_begin();

			for (Date d = week.get_begin(); d <= week.get_end(); d++)
				(*this) << display_day << d;

			(*this) << fill_week_end << week.get_end();
		}
		else
			(*this) << empty_week_fill;

		_out << std::endl;
	} // endfor weeks.

	return (*this);
}


CalendarFormat &CalendarFormat::operator<<(const Calendar &cal)
{
	Month line_start;
	Month line_end;
	Month month;
	Week week;

	// Display line of months.
	for (line_start = Month(cal.get_begin()); line_start < Month(cal.get_end()); line_start += cal.get_width())
	{
		line_end = line_start + cal.get_width();

		// Display month name.
		for (month = Month(line_start); month < line_end; month++)
			(*this) << display_month_name << month;
		_out << std::endl;

		// Display names of days in the week.
		_out << std::right;
		for (month = Month(line_start); month < line_end; month++)
			(*this) << display_week_header;
		_out << std::endl;

		// Display by each week of each month in line.
		for (int week_num = 0; week_num < 6; week_num++)
		{
			for (month = Month(line_start); month < line_end; month++)
			{
				week = Week(month.get_begin()) + week_num;

				if (week.get_begin() <= month.get_end())
				{
					(*this) << fill_week_begin << week.get_begin();

					for (Date d = week.get_begin(); d <= week.get_end(); d++)
						(*this) << display_day << d;

					(*this) << fill_week_end << week.get_end();
				}
				else
					(*this) << empty_week_fill;

				_out << _space_symbol;
			} // endfor months in line.

			_out << std::endl;
		} // endfor weeks.

		_out << std::endl;
	} // endfor month line.

	return (*this);
}

CalendarFormat (*ololo)(std::ostream&) = init_format;
