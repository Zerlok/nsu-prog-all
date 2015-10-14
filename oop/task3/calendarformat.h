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


enum class Display
{
	none = 0,
	day_num = 1,
	month_name = 2,
	week_begin = 3,
	week_end = 4,
};


class CalendarFormat;


// CalendarFormat manipulators.
namespace cf
{
	CalendarFormat format();
	CalendarFormat format(std::ostream &out);
	CalendarFormat &horizontal(CalendarFormat &format);
	CalendarFormat &vertical(CalendarFormat &format);
	CalendarFormat &day_number(CalendarFormat &format);
	CalendarFormat &month_name(CalendarFormat &format);
	CalendarFormat &week_header(CalendarFormat &format);
	CalendarFormat &fill_empty_week_horizontal(CalendarFormat &format);
	CalendarFormat &fill_week_begin(CalendarFormat &format);
	CalendarFormat &fill_week_end(CalendarFormat &format);
}


class CalendarFormat
{
	public:
		// Manipulators.
		friend CalendarFormat &cf::horizontal(CalendarFormat &format);
		friend CalendarFormat &cf::vertical(CalendarFormat &format);
		friend CalendarFormat &cf::day_number(CalendarFormat &format);
		friend CalendarFormat &cf::month_name(CalendarFormat &format);
		friend CalendarFormat &cf::week_header(CalendarFormat &format);
		friend CalendarFormat &cf::fill_empty_week_horizontal(CalendarFormat &format);
		friend CalendarFormat &cf::fill_week_begin(CalendarFormat &format);
		friend CalendarFormat &cf::fill_week_end(CalendarFormat &format);

		// Constructors / Destructor.
		CalendarFormat();
		CalendarFormat(std::ostream &out);
		~CalendarFormat();

		// Operators.
		CalendarFormat &operator<<(const char chr);
		CalendarFormat &operator<<(const Date &date);
		CalendarFormat &operator<<(const Week &week);
		CalendarFormat &operator<<(const Month &month);
		CalendarFormat &operator<<(const Calendar &calendar);

		// Operators for Manipulators.
		CalendarFormat &operator<<(std::ostream& (*func)(std::ostream&)) { _out << func; return (*this); }
		CalendarFormat &operator<<(CalendarFormat& (*func)(CalendarFormat&)) { return func(*this); }

		// Modifiers.
		void set_day_width(int n);

	private:
		// Static.
		static const int DEFAULT_DAY_WIDTH;
		static const char SPACE_SYMBOL;

		// Fields.
		Direction _calendar_direction;
		Display _display;

		char _space_symbol;

		int _day_width;
		int _week_width;

		std::ostream &_out;

		// Methods.
		void init();
		void turn_flags_false();

		void horizontal_display(const Calendar &cal);
		void vertical_display(const Calendar &cal);
};


// For format init.
CalendarFormat operator<<(std::ostream &out, CalendarFormat (*func)(std::ostream&));

// __CALENDARFORMAT_H__
#endif
