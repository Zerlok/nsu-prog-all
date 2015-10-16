#ifndef __CALENDARPARSER_H__
#define __CALENDARPARSER_H__


#include <vector>
#include <string>
#include <unordered_map>

#include "date.h"
#include "calendarformat.h"


class CalendarParser;

typedef	void (*str_parser_ptr)(CalendarParser&, std::vector<std::string>::const_iterator&);
void direction_parser(CalendarParser &parser, std::vector<std::string>::const_iterator &it);
void year_display_parser(CalendarParser &parser, std::vector<std::string>::const_iterator &it);
void period_parser(CalendarParser &parser, std::vector<std::string>::const_iterator &it);

static const std::unordered_map< std::string, str_parser_ptr > ARGUMENT_PARSERS  = {
	{"horiz", direction_parser},
	{"vert", direction_parser},

	{"year_once", year_display_parser},
	{"year_for_each_month", year_display_parser},

	{"year", period_parser},
	{"month", period_parser},
	{"range", period_parser}
};


class CalendarParser
{
	public:
		// Constructors / Destructor.
		CalendarParser(int argc, char **argv);
		~CalendarParser();

		// Getters.
		const Date &get_calendar_begin() const { return _calendar_begin; }
		const Date &get_calendar_end() const { return _calendar_end; }
		CalendarFormat get_calendar_format() const { return _calendar_format; }

		// Friends.
		friend void direction_parser(CalendarParser&, std::vector<std::string>::const_iterator&);
		friend void year_display_parser(CalendarParser&, std::vector<std::string>::const_iterator&);
		friend void period_parser(CalendarParser&, std::vector<std::string>::const_iterator&);

	private:
		// Fields.
		std::vector<std::string> _args;

		Date _calendar_begin;
		Date _calendar_end;

		CalendarFormat _calendar_format;
};



// __CALENDARPARSER_H__
#endif
