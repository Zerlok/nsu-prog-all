#include <iostream>
#include "calendarformat.h"


CalendarFormat::CalendarFormat(std::string &str_format)
{
	_direction = vertical;
	_print_year_once = true;
}


CalendarFormat::CalendarFormat(const CalendarFormat &format)
	: _direction(format._direction), _print_year_once(format._print_year_once)
{

}


CalendarFormat::~CalendarFormat()
{

}


std::ostream &CalendarFormat::view(std::ostream &out, const Date &date)
{
	return out << date;
}
