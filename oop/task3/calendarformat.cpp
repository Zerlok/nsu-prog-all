#include <iomanip>

#include "calendarformat.h"


// ------------------- Constants ------------------- //

const int CalendarFormat::DEFAULT_DAY_WIDTH = 3;
const int CalendarFormat::DEFAULT_CALENDAR_WIDTH = 3;
const char CalendarFormat::DEFAULT_SPACE_SYMBOL = ' ';
const char CalendarFormat::DEFAULT_ZERO_DAY_SYMBOL = ' ';


// ------------------- Manipulators ------------------- //

CalendarFormat &cf::horizontal(CalendarFormat &format)
{
	format._calendar_direction = Direction::horizontal;
	format.set_day_width(format._day_width);
	return format;
}


CalendarFormat &cf::vertical(CalendarFormat &format)
{
	format._calendar_direction = Direction::vertical;
	format.set_day_width(format._day_width);
	return format;
}


CalendarFormat &cf::day(CalendarFormat &format)
{
	format._display = Display::day;
	format._out << std::setfill(format._space_symbol) << std::setw(format._day_width);

	return format;
}


CalendarFormat &cf::year(CalendarFormat &format)
{
	format._display = Display::year;
	format._out << std::setfill(format._space_symbol) << std::setw(format._calendar_width * (format._week_width+1) / 2);

	return format;
}


CalendarFormat &cf::month_name(CalendarFormat &format)
{
	format._display = Display::month_header;
	format._out << std::setfill(format._space_symbol);

	if (format._month_header == MonthHeader::year_once)
		format._out << std::setw(format._week_width);

	else if (format._month_header == MonthHeader::year_for_each_month)
		format._out << std::setw(format._week_width - 5);

	return format;
}


CalendarFormat &cf::week_header(CalendarFormat &format)
{
	format._out << std::setfill(format._space_symbol);

	for (int i = 0; i < 7; i++)
		format._out << std::setw(format._day_width)
			<< WEEKDAY_NAMES[i].substr(0, format._day_width - 1);

	return format;
}


CalendarFormat &cf::fill_empty_week_horizontal(CalendarFormat &format)
{
	format._out << std::setfill(format._space_symbol)
			<< std::setw(format._week_width)
			<< format._zero_day_symbol;

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


CalendarFormat &cf::display_year_once(CalendarFormat &format)
{
	format._month_header = MonthHeader::year_once;
	return format;
}


CalendarFormat &cf::display_year_for_each_month(CalendarFormat &format)
{
	format._month_header = MonthHeader::year_for_each_month;
	return format;
}


// ------------------- CalendarFormat ------------------- //

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


CalendarFormat::CalendarFormat(const CalendarFormat &format)
	: _out(format._out)
{
	_display = format._display;
	_calendar_direction = format._calendar_direction;
	_month_header = format._month_header;

	set_day_width(format._day_width);
	set_calendar_width(format._calendar_width);
	set_space_symbol(format._space_symbol);
	set_zero_day_symbol(format._zero_day_symbol);
}


CalendarFormat::~CalendarFormat()
{
}


void CalendarFormat::init()
{
	_calendar_direction = Direction::horizontal;
	_display = Display::none;
	_month_header = MonthHeader::year_once;

	set_day_width(CalendarFormat::DEFAULT_DAY_WIDTH);
	set_calendar_width(CalendarFormat::DEFAULT_CALENDAR_WIDTH);
	set_space_symbol(CalendarFormat::DEFAULT_SPACE_SYMBOL);
	set_zero_day_symbol(CalendarFormat::DEFAULT_ZERO_DAY_SYMBOL);
}


CalendarFormat operator<<(std::ostream &out, CalendarFormat& (*func)(CalendarFormat&))
{
	CalendarFormat f(out);
	return func(f);
}


CalendarFormat &CalendarFormat::operator<<(const char chr)
{
	if (_display == Display::day)
		_display = Display::none;

	_out << chr;
	return (*this);
}


CalendarFormat &CalendarFormat::operator<<(const Date &date)
{
	switch (_display)
	{
		case Display::day:
		{
			_out << date.get_day();
			break;
		}

		case Display::month_header:
		{
			_out << date.get_month_name();
			break;
		}

		case Display::year:
		{
			_out << date.get_year();
			break;
		}

		case Display::week_begin:
		{
			for (int i = 0; i < date.get_weekday(); i++)
				_out << std::setw(_day_width) << _space_symbol;
			break;
		}

		case Display::week_end:
		{
			for (int i = date.get_weekday(); i < DAYS_IN_WEEK_NUM - 1; i++)
				_out << std::setw(_day_width) << _space_symbol;
			break;
		}

		case Display::none:
		default:
		{
			_out << "["
					<< date.get_weekday_name().substr(0, _day_width) << ' '
					<< date.get_day() << ' '
					<< date.get_month_name().substr(0, _day_width) << ' '
					<< date.get_year()
					<< "]";
		}
	}

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
	if (_display == Display::month_header)
	{
		_out << month.get_name();

		if (_month_header == MonthHeader::year_for_each_month)
			_out << _space_symbol << month.get_year();
	}
	else if ((_display == Display::year)
			 && (_month_header == MonthHeader::year_once))
		_out << month.get_year() << std::endl;

	_display = Display::none;
	return (*this);
}


CalendarFormat &CalendarFormat::operator<<(const Calendar &cal)
{
	_out << std::right;

	if (_calendar_direction == Direction::horizontal)
		horizontal_display(cal);

	else if (_calendar_direction == Direction::vertical)
		vertical_display(cal);

	_out << std::left;
	return (*this);
}


void CalendarFormat::set_day_width(int n)
{
	if (n < 2)
		return;

	_day_width = n;

	if (_calendar_direction == Direction::horizontal)
		_week_width = _day_width * DAYS_IN_WEEK_NUM;

	else if (_calendar_direction == Direction::vertical)
		_week_width = _day_width * MAX_WEEKS_IN_MONTH_NUM;
}


void CalendarFormat::set_calendar_width(int n)
{
	if ((n < 1)
			&& (n > MONTHS_IN_YEAR_NUM / 2))
		return;

	_calendar_width = n;
}


void CalendarFormat::horizontal_display(const Calendar &cal)
{
	Month line_end(cal.get_begin());
	Month line_start;
	Month month;
	Week week;
	Date d;

	// Display line of months.
	for (line_start = Month(cal.get_begin());
		 line_start <= Month(cal.get_end());
		 increment_line_start(line_start, _calendar_width))
	{
		increment_line_end(line_end, line_start, cal.get_end(), _calendar_width);
		line_header_display(line_start, line_end, cal.get_begin());

		// Display names of days in the week.
		for (month = Month(line_start); month < line_end; month++)
			(*this) << cf::week_header << _space_symbol;
		_out << std::endl;

		// Display by each week of each month in line.
		for (int week_num = 0; week_num < MAX_WEEKS_IN_MONTH_NUM; week_num++)
		{
			for (month = Month(line_start); month < line_end; month++)
			{
				week = Week(month.get_begin()) + week_num;

				if (week.get_begin() <= month.get_end())
				{
					(*this) << cf::fill_week_begin << week.get_begin();

					for (d = week.get_begin(); d <= week.get_end(); d++)
						(*this) << cf::day << d;

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
	Month line_end(cal.get_begin());
	Month line_start;
	Month month;
	Week week;
	Date week_begin;
	Date d;
	int week_num;

	// For each calendar line.
	for (line_start = Month(cal.get_begin());
		 line_start <= Month(cal.get_end());
		 increment_line_start(line_start, cal.get_width()))
	{
		increment_line_end(line_end, line_start, cal.get_end(), cal.get_width());
		line_header_display(line_start, line_end, cal.get_begin());
		_out << std::right;

		// For each weekday (line).
		for (int weekday_num = 0; weekday_num < DAYS_IN_WEEK_NUM; weekday_num++)
		{
			// For each month in line.
			for (month = Month(line_start); month < line_end; month++)
			{
				// Display weekdays.
				if (month == line_start)
					_out << WEEKDAY_NAMES[weekday_num].substr(0, _day_width-1);

				// For each week in month.
				week = Week(month.get_begin());
				for (week_num = 0; week_num < MAX_WEEKS_IN_MONTH_NUM; week_num++)
				{
					week_begin = week.get_begin();
					d = week_begin + (weekday_num - week_begin.get_weekday());

					if ((week.is_contain(d))
							&& (week <= month.get_end()))
						(*this) << cf::day << d;

					else
						(*this) << cf::day << _zero_day_symbol;

					week++;
				} // endfor weeks in month.

				_out << _space_symbol;
			} // endfor months in line.

			_out << std::endl;
		} // endfor each weekday (line).

		_out << std::endl;
	} // endfor calendar line.
}


void CalendarFormat::increment_line_start(Month &line_start, int width)
{
	Month m(line_start);

	line_start += width;

	if (line_start.get_year() > m.get_year())
		line_start = Month(Date(m.get_year()+1, 1, 1));
}


void CalendarFormat::increment_line_end(Month &line_end, const Month &line_start, const Date &cal_end, int width)
{
	// set last month at line.
	line_end = line_start + width;

	// recalculate last month, if it ends after calendar end.
	if (line_end > cal_end)
		line_end = Month(cal_end) + 1;

	if (line_end.get_year() > line_start.get_year())
		line_end = Month(Date(line_end.get_year(), 1, 1));
}


void CalendarFormat::line_header_display(const Month &start, const Month &end, const Date &cal_begin)
{
	// Display year.
	if ((start.get_number() == 1)
			|| (start.get_begin() == cal_begin))
		(*this) << cf::year << start;

	// Display month name.
	for (Month month(start); month < end; month++)
		(*this) << cf::month_name << month << _space_symbol;
	_out << std::endl;
}
