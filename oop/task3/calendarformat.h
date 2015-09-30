#ifndef __CALENDARFORMAT_H__
#define __CALENDARFORMAT_H__


#include <string>


enum Direction
{
	vertical,
	horizontal
};


class CalendarFormat
{
	public:
		CalendarFormat(std::string &str_format);
		CalendarFormat(const CalendarFormat &format);

	private:
		Direction _direction;
		bool _print_year_once;
};


// __CALENDARFORMAT_H__
#endif
