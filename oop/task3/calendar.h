#ifndef __CALENDAR_H__
#define __CALENDAR_H__


#include <iostream>

#include "date.h"


class Calendar
{
	public:
		// Constructors / Destructor.
		Calendar(const Date &date);
		Calendar(const Date& begin, const Date& end);
		Calendar(const int year);
		~Calendar();

		// Operators.
		friend std::ostream &operator<<(std::ostream &out, const Calendar &cal);

		// Getters.
		const Date &get_begin() const { return _begin; }
		const Date &get_end() const { return _end; }
		int get_width() const { return _width; }

	private:
		// Static.
		static const int DEFAULT_WIDTH;

		// Fields.
		Date _begin;
		Date _end;

		int _width;
};


// Friends.
std::ostream &operator<<(std::ostream &out, const Calendar &cal);


// __CALENDAR_H__
#endif
