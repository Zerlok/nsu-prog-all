#include <iomanip>
#include <string>
#include <sstream>

#include "calendarformat.h"


const char CalendarFormat::SPACE_SYMBOL = ' ';


CalendarFormat cf::format()
{
	return CalendarFormat();
}


CalendarFormat cf::format(std::ostream &out)
{
	return CalendarFormat(out);
}


CalendarFormat &horiz(CalendarFormat &format)
{
	format._calendar_direction = horizontal;
	return format;
}


CalendarFormat &vertic(CalendarFormat &format)
{
	format._calendar_direction = vertical;
	return format;
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

	format._out << format._space_symbol;
	return format;
}


CalendarFormat &empty_week_fill(CalendarFormat &format)
{
	format._out << std::setfill(format._space_symbol)
			<< std::setw(format._week_width)
			<< format._space_symbol;

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


CalendarFormat::~CalendarFormat()
{
}


void CalendarFormat::init()
{
	turn_flags_false();
	_day_width = 4;
	_week_width = _day_width * 7;
	_calendar_direction = horizontal;
	_space_symbol = CalendarFormat::SPACE_SYMBOL;
}


void CalendarFormat::turn_flags_false()
{
	_day_display		= false;
	_month_name_display	= false;
	_week_begin_fill	= false;
	_week_end_fill		= false;
}


CalendarFormat operator<<(std::ostream &out, CalendarFormat (*func)(std::ostream&))
{
	return func(out);
}


CalendarFormat &CalendarFormat::operator<<(const char chr)
{
	_out << chr;
	return (*this);
}


CalendarFormat &CalendarFormat::operator<<(const Date &date)
{
	if (_day_display)
		_out << date.get_day();

	else if (_month_name_display)
		_out << date.get_month_name() << _space_symbol;

	else if (_week_begin_fill)
		for (int i = 0; i < date.get_weekday(); i++)
			_out << std::setw(_day_width) << _space_symbol;

	else if (_week_end_fill)
		for (int i = date.get_weekday(); i < 6; i++)
			_out << std::setw(_day_width) << _space_symbol;

	else
		_out << "["
				<< date.get_weekday_name().substr(0, _day_width) << ' '
				<< date.get_day() << ' '
				<< date.get_month_name().substr(0, _day_width) << ' '
				<< date.get_year()
				<< "]";

	turn_flags_false();
	return (*this);
}


CalendarFormat &CalendarFormat::operator<<(const Week &week)
{
	_out << week;
	return (*this);
}


CalendarFormat &CalendarFormat::operator<<(const Month &month)
{
	return (*this) << month.get_begin();
}


CalendarFormat &CalendarFormat::operator<<(const Calendar &cal)
{
	std::cout << cal << std::endl;

	if (_calendar_direction == horizontal)
		horizontal_display(cal);

	else
		vertical_display(cal);

	return (*this);
}


void CalendarFormat::horizontal_display(const Calendar &cal)
{
	Month line_start;
	Month line_end;
	Month month;
	Week week;
	Date d;

	// Display line of months.
	for (line_start = Month(cal.get_begin()); line_start < Month(cal.get_end()); line_start += cal.get_width())
	{
		line_end = line_start + cal.get_width();

		if (line_end > cal.get_end())
			line_end = Month(cal.get_end()) + 1;

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

					for (d = week.get_begin(); d <= week.get_end(); d++)
						(*this) << display_day << d;

					(*this) << fill_week_end << week.get_end();
				}
				else
					(*this) << empty_week_fill;

				_out << _space_symbol;
			} // endfor months in line.

			_out << std::endl;
		} // endfor weeks.

	} // endfor month line.
}


void CalendarFormat::vertical_display(const Calendar &cal)
{
	Month line_start;
	Month line_end;
	Month month;
	Week week;
	Date d;

	// Display line of months.
	for (line_start = Month(cal.get_begin()); line_start <= Month(cal.get_end()); line_start += cal.get_width())
	{
		line_end = line_start + cal.get_width();

		if (line_end > cal.get_end())
			line_end = cal.get_end();

		// Display month name.
		for (month = Month(line_start); month < line_end; month++)
			(*this) << display_month_name << month << _space_symbol;
		_out << std::endl;
		_out << std::right;

		// For each weekday.
		for (int weekday_num = 0; weekday_num < 7; weekday_num++)
		{
			// Display by each week of each month in line.
			for (month = Month(line_start); month < line_end; month++)
			{
				if (month == line_start)
					_out << WEEKDAY_NAMES[weekday_num].substr(0, _day_width-1) << _space_symbol;

				for (week = Week(month.get_begin()); week <= month.get_end(); week++)
				{
					d = week.get_begin();
					if ((d.get_weekday() <= weekday_num)
							&& (week.get_end() >= weekday_num))
						(*this) << display_day << d + (weekday_num - d.get_weekday());

					else
						(*this) << display_day << _space_symbol;

					_out << _space_symbol;
				} // endfor weeks.

				_out << std::endl;
			} // endfor months in line.
		}

	} // endfor month line.
}
