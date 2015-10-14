#ifndef __CALENDARFORMAT_H__
#define __CALENDARFORMAT_H__


#include <iostream>

#include "date.h"
#include "week.h"
#include "month.h"
#include "calendar.h"


enum Direction
{
	horizontal = 0,
	vertical = 1,
};


class CalendarFormat
{
	public:
		// ???
		friend CalendarFormat init_format(std::ostream &out);

		friend CalendarFormat &horiz(CalendarFormat &format);
		friend CalendarFormat &vertic(CalendarFormat &format);
		friend CalendarFormat &display_day(CalendarFormat &format);
		friend CalendarFormat &display_month_name(CalendarFormat &format);
		friend CalendarFormat &display_week_header(CalendarFormat &format);
		friend CalendarFormat &empty_week_fill(CalendarFormat &format);
		friend CalendarFormat &fill_week_begin(CalendarFormat &format);
		friend CalendarFormat &fill_week_end(CalendarFormat &format);

		// Constructors / Destructor.
		CalendarFormat();
		CalendarFormat(std::ostream &out);
		~CalendarFormat();

		// Manipulators.
		CalendarFormat &operator<<(std::ostream& (*func)(std::ostream&)) { _out << func; return (*this); }
		CalendarFormat &operator<<(CalendarFormat& (*func)(CalendarFormat&)) { return func(*this); }

		// Operators.
		CalendarFormat &operator<<(const char chr);
		CalendarFormat &operator<<(const Date &date);
		CalendarFormat &operator<<(const Week &week);
		CalendarFormat &operator<<(const Month &month);
		CalendarFormat &operator<<(const Calendar &calendar);

	private:
		// Static.
		static const char SPACE_SYMBOL;

		// Fields.
		Direction _calendar_direction;

		bool _day_display;
		bool _month_name_display;
		bool _week_begin_fill;
		bool _week_end_fill;

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

// Friends.
namespace cf {
	CalendarFormat format();
	CalendarFormat format(std::ostream &out);
}

CalendarFormat &horiz(CalendarFormat &format);
CalendarFormat &vertic(CalendarFormat &format);
CalendarFormat &display_day(std::ostream &out);
CalendarFormat &display_month_name(std::ostream &out);
CalendarFormat &display_week_header(std::ostream &out);
CalendarFormat &empty_week_fill(CalendarFormat &format);
CalendarFormat &fill_week_begin(CalendarFormat &format);
CalendarFormat &fill_week_end(CalendarFormat &format);


// For format init.
CalendarFormat operator<<(std::ostream &out, CalendarFormat (*func)(std::ostream&));
//CalendarFormat operator<<(const CalendarFormat *format, CalendarFormat (*func)(CalendarFormat&));

// __CALENDARFORMAT_H__
#endif
