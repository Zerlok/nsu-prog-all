#ifndef __CALENDAR_H__
#define __CALENDAR_H__


#include <iostream>

#include "date.h"
#include "calendarformat.h"


class Calendar
{
	public:
		Calendar(
				const Date &begin,
				const CalendarFormat &format
		);
		Calendar(
				const Date& begin,
				const Date& end,
				const CalendarFormat& format
		);
		Calendar(
				const int year,
				const CalendarFormat &format
		);
		~Calendar();

		friend std::ostream& operator<<(std::iostream& out, Calendar& cal);

		void set_format(const CalendarFormat& format);

	private:
		Date _begin;
		Date _end;
		CalendarFormat _format;
};

std::ostream& operator<<(std::iostream& out, Calendar& cal);


// __CALENDAR_H__
#endif
