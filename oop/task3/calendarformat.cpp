#include <iomanip>
#include <string>
#include <sstream>

#include "calendarformat.h"


const int CalendarFormat::DEFAULT_DAY_WIDTH = 3;
const char CalendarFormat::SPACE_SYMBOL = ' ';


CalendarFormat cf::format()
{
	return CalendarFormat();
}


CalendarFormat cf::format(std::ostream &out)
{
	return CalendarFormat(out);
}


CalendarFormat &cf::horizontal(CalendarFormat &format)
{
	format._calendar_direction = Direction::horizontal;
	return format;
}


CalendarFormat &cf::vertical(CalendarFormat &format)
{
	format._calendar_direction = Direction::vertical;
	return format;
}


CalendarFormat &cf::day_number(CalendarFormat &format)
{
	format._display = Display::day_num;
	format._out << std::setfill(format._space_symbol) << std::setw(format._day_width);

	return format;
}


CalendarFormat &cf::month_name(CalendarFormat &format)
{
	format._display = Display::month_name;
	format._out << std::setfill(format._space_symbol) << std::setw(format._week_width);

	return format;
}


CalendarFormat &cf::week_header(CalendarFormat &format)
{
	format._out << std::setfill(format._space_symbol);

	for (int i = 0; i < 7; i++)
		format._out << std::setw(format._day_width)
			<< WEEKDAY_NAMES[i].substr(0, format._day_width - 1);

	format._out << format._space_symbol;
	return format;
}


CalendarFormat &cf::fill_empty_week_horizontal(CalendarFormat &format)
{
	format._out << std::setfill(format._space_symbol)
			<< std::setw(format._week_width)
			<< format._space_symbol;

	return format;
}


CalendarFormat &cf::fill_week_begin(CalendarFormat &format)
{
	format._display = Display::week_begin;
	format._out << std::setfill(format._space_symbol);

	return format;
}


CalendarFormat &cf::fill_week_end(CalendarFormat &format)
{
	format._display = Display::week_end;
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
	_display = Display::none;
	set_day_width(CalendarFormat::DEFAULT_DAY_WIDTH);
	_calendar_direction = Direction::horizontal;
	_space_symbol = CalendarFormat::SPACE_SYMBOL;
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
	if (_display == Display::day_num)
		_out << date.get_day();

	else if (_display == Display::month_name)
		_out << date.get_month_name() << _space_symbol;

	else if (_display == Display::week_begin)
		for (int i = 0; i < date.get_weekday(); i++)
			_out << std::setw(_day_width) << _space_symbol;

	else if (_display == Display::week_end)
		for (int i = date.get_weekday(); i < DAYS_IN_WEEK_NUM - 1; i++)
			_out << std::setw(_day_width) << _space_symbol;

	else if (_display == Display::none)
		_out << "["
				<< date.get_weekday_name().substr(0, _day_width) << ' '
				<< date.get_day() << ' '
				<< date.get_month_name().substr(0, _day_width) << ' '
				<< date.get_year()
				<< "]";

	_display = Display::none;
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

	if (_calendar_direction == Direction::horizontal)
		horizontal_display(cal);

	else
		vertical_display(cal);

	return (*this);
}


void CalendarFormat::set_day_width(int n)
{
	if (n < 2)
		return;

	_day_width = n;
	_week_width = _day_width * DAYS_IN_WEEK_NUM;
}


void CalendarFormat::horizontal_display(const Calendar &cal)
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
			line_end = (Month(cal.get_end()) + 1).get_end();

		// Display month name.
		for (month = Month(line_start); month < line_end; month++)
			(*this) << cf::month_name << month;
		_out << std::endl;

		// Display names of days in the week.
		_out << std::right;
		for (month = Month(line_start); month < line_end; month++)
			(*this) << cf::week_header;
		_out << std::endl;

		// Display by each week of each month in line.
		for (int week_num = 0; week_num < DAYS_IN_WEEK_NUM - 1; week_num++)
		{
			for (month = Month(line_start); month < line_end; month++)
			{
				week = Week(month.get_begin()) + week_num;

				if (week.get_begin() <= month.get_end())
				{
					(*this) << cf::fill_week_begin << week.get_begin();

					for (d = week.get_begin(); d <= week.get_end(); d++)
						(*this) << cf::day_number << d;

					(*this) << cf::fill_week_end << week.get_end();
				}
				else
					(*this) << cf::fill_empty_week_horizontal;

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
	Date week_begin;
	Date d;

	// Display line of months.
	for (line_start = Month(cal.get_begin()); line_start <= Month(cal.get_end()); line_start += cal.get_width())
	{
		line_end = line_start + cal.get_width();

		if (line_end > cal.get_end())
			line_end = (Month(cal.get_end()) + 1).get_end();

		// Display month name.
		for (month = Month(line_start); month < line_end; month++)
			(*this) << cf::month_name << month << _space_symbol;
		_out << std::endl;
		_out << std::right;

		// For each weekday.
		for (int weekday_num = 0; weekday_num < DAYS_IN_WEEK_NUM; weekday_num++)
		{
			// Display by each week of each month in line.
			for (month = Month(line_start); month < line_end; month++)
			{
				if (month == line_start)
					_out << WEEKDAY_NAMES[weekday_num].substr(0, _day_width);

				for (week = Week(month.get_begin()); week <= month.get_end(); week++)
				{
					week_begin = week.get_begin();
					d = week_begin + (weekday_num - week_begin.get_weekday());

					if (week.is_contain(d))
						(*this) << cf::day_number << d;

					else
						(*this) << cf::day_number << _space_symbol;

					_out << _space_symbol;
				} // endfor weeks.

				_out << _space_symbol;
			} // endfor months in line.

			_out << std::endl;
		}

		_out << std::endl;
	} // endfor month line.
}
