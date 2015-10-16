#ifndef __CALENDARFORMAT_H__
#define __CALENDARFORMAT_H__


#include <iostream>

#include "date.h"
#include "week.h"
#include "month.h"
#include "calendar.h"


enum class Direction
{
	horizontal = 0,
	vertical = 1,
};


enum class DateDisplay
{
	none = 0,
	day_num = 1,
	month_name = 2,
	week_begin = 3,
	week_end = 4,
};


enum class MonthDisplay
{
	year_once = 0,
	year_for_each_month = 1,
};


// CalendarFormat manipulators.
class CalendarFormat;
namespace cf
{
	CalendarFormat &horizontal(CalendarFormat &format);
	CalendarFormat &vertical(CalendarFormat &format);
	CalendarFormat &day_number(CalendarFormat &format);
	CalendarFormat &month_name(CalendarFormat &format);
	CalendarFormat &week_header(CalendarFormat &format);
	CalendarFormat &fill_empty_week_horizontal(CalendarFormat &format);
	CalendarFormat &fill_week_begin(CalendarFormat &format);
	CalendarFormat &fill_week_end(CalendarFormat &format);
	CalendarFormat &display_year_once(CalendarFormat &format);
	CalendarFormat &display_year_for_each_month(CalendarFormat &format);
}


class CalendarFormat
{
	public:
		// Constructors / Destructor.
		CalendarFormat();
		CalendarFormat(std::ostream &out);
		CalendarFormat(const CalendarFormat &format);
		~CalendarFormat();

		// Operators.
		CalendarFormat &operator<<(const char chr);
		CalendarFormat &operator<<(const Date &date);
		CalendarFormat &operator<<(const Week &week);
		CalendarFormat &operator<<(const Month &month);
		CalendarFormat &operator<<(const Calendar &calendar);

		// Setters.
		void set_day_width(int n);
		void set_calendar_width(int n);
		void set_space_symbol(char chr) { _space_symbol = chr; }
		void set_zero_day_symbol(char chr) { _zero_day_symbol = chr; }

		// Operators for Manipulators.
		CalendarFormat &operator<<(std::ostream& (*func)(std::ostream&)) { _out << func; return (*this); }
		CalendarFormat &operator<<(CalendarFormat& (*func)(CalendarFormat&)) { return func(*this); }

		// Manipulators (friends).
		friend CalendarFormat &cf::horizontal(CalendarFormat &format);
		friend CalendarFormat &cf::vertical(CalendarFormat &format);
		friend CalendarFormat &cf::day_number(CalendarFormat &format);
		friend CalendarFormat &cf::month_name(CalendarFormat &format);
		friend CalendarFormat &cf::week_header(CalendarFormat &format);
		friend CalendarFormat &cf::fill_empty_week_horizontal(CalendarFormat &format);
		friend CalendarFormat &cf::fill_week_begin(CalendarFormat &format);
		friend CalendarFormat &cf::fill_week_end(CalendarFormat &format);
		friend CalendarFormat &cf::display_year_once(CalendarFormat &format);
		friend CalendarFormat &cf::display_year_for_each_month(CalendarFormat &format);

	private:
		// Static.
		static const int DEFAULT_CALENDAR_WIDTH;
		static const int DEFAULT_DAY_WIDTH;
		static const char DEFAULT_SPACE_SYMBOL;
		static const char DEFAULT_ZERO_DAY_SYMBOL;

		// Fields.
		std::ostream &_out;

		Direction _calendar_direction;
		DateDisplay _date_display;
		MonthDisplay _month_display;

		int _day_width;
		int _week_width;
		int _calendar_width;

		char _space_symbol;
		char _zero_day_symbol;

		// Methods.
		void init();

		void horizontal_display(const Calendar &cal);
		void vertical_display(const Calendar &cal);
};


// For format init (each manipulator call with '<<' operator creates CalendarFormat).
CalendarFormat operator<<(std::ostream &out, CalendarFormat& (*func)(CalendarFormat&));

// __CALENDARFORMAT_H__
#endif
