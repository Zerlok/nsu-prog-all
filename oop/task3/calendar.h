#ifndef __CALENDAR_H__
#define __CALENDAR_H__


#include <iostream>
#include <iomanip>

#include "date.h"


enum Direction
{
	vertical,
	horizontal
};


class Calendar
{
	public:
		// Constructors / Destructor.
		Calendar(const Date& begin, const Date& end);
		Calendar(const int year);
		~Calendar();

		// Operators.
		friend std::ostream &operator<<(std::ostream &out, const Calendar &cal);

	private:
		// Fields.
		Date _begin;
		Date _end;
};

std::ostream &operator<<(std::ostream &out, const Calendar &cal);


// __CALENDAR_H__
#endif
