#include "calendarparser.h"


CalendarParser::CalendarParser(int argc, char **argv)
	: _calendar_begin(Date()), _calendar_end(Date()), _calendar_format()
{
	for (int i = 1; i < argc; i++)
		_args.push_back(argv[i]);

	for (std::vector<std::string>::const_iterator arg = _args.begin();
		 arg != _args.end();
		 arg++)
	{
		auto const it = ARGUMENT_PARSERS.find(*arg);

		if (it != ARGUMENT_PARSERS.end())
			it->second(*this, arg);
	}
}


CalendarParser::~CalendarParser()
{
}


void direction_parser(CalendarParser &parser, std::vector<std::string>::const_iterator &it)
{
	const std::string &value = (*it);

	if (!value.compare("vert"))
		parser._calendar_format << cf::vertical;

	else if (!value.compare("horiz"))
		parser._calendar_format << cf::horizontal;
}


void year_display_parser(CalendarParser &parser, std::vector<std::string>::const_iterator &it)
{
	const std::string &value = (*it);

	if (!value.compare("year_once"))
		parser._calendar_format << cf::display_year_once;

	else if (!value.compare("year_for_each_month"))
		parser._calendar_format << cf::display_year_for_each_month;
}


void period_parser(CalendarParser &parser, std::vector<std::string>::const_iterator &it)
{
	const std::string &value = (*it);
	const Date today = Date();

	if (!value.compare("year"))
	{
		int year = std::stoi(*(it + 1));
		parser._calendar_begin = Date(year, 1, 1);
		parser._calendar_end = Date(year+1, 1, 1) - 1;
	}
	else if (!value.compare("month"))
	{
		int month = std::stoi(*(it + 1));
		parser._calendar_begin = Date(today.get_year(), month, 1);
		parser._calendar_end = parser._calendar_begin;
	}
	else if (!value.compare("range"))
	{
		parser._calendar_begin = Date(std::stoi(*(it + 1)), std::stoi(*(it + 2)));
		parser._calendar_end = Date(std::stoi(*(it + 3)), std::stoi(*(it + 4)));
	}
}
