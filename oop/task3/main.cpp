#include <iostream>
#include <iomanip>
#include <sstream>

#include "date.h"
#include "week.h"
#include "month.h"
#include "calendar.h"
#include "calendarformat.h"

#include "argvparser.h"


class InputData
{
	public:
		CalendarFormat format;
		Calendar calendar;
};


void display_calendar_vertical(const ArgvFlag &flag, InputData &data)
{
	data.format << cf::vertical;
}


void display_calendar_horizontal(const ArgvFlag &flag, InputData &data)
{
	data.format << cf::horizontal;
}


void show_year_for_each_month(const ArgvFlag &flag, InputData &data)
{
	data.format << cf::display_year_for_each_month;
}


void show_year_once(const ArgvFlag &flag, InputData &data)
{
	data.format << cf::display_year_once;
}


void calendar_for_year(const ArgvFlag &flag, InputData &data)
{
	if (flag.get_params_num() != 1)
		throw std::invalid_argument("1 argument required (year)!");

	data.calendar = Calendar(stoi(flag[0]));
}


void calendar_for_month(const ArgvFlag &flag, InputData &data)
{
	if (flag.get_params_num() != 1)
		throw std::invalid_argument("1 argument required (month)!");

	int current_year = Date().get_year();
	int month = stoi(flag[0]);

	data.calendar = Calendar(
			Date::create_month_begin(current_year, month),
			Date::create_month_end(current_year, month)
	);
}


void custom_ranged_calendar(const ArgvFlag &flag, InputData &data)
{
	int params_num = flag.get_params_num();

	if (params_num == 0)
		return;

	if (params_num < 4)
		throw std::invalid_argument("4 arguments required (year1 month1 year2 month2)!");

	data.calendar = Calendar(
			Date(stoi(flag[0]), stoi(flag[1])),
			Date(stoi(flag[2]), stoi(flag[3]))
	);
}


int main(int argc, char *argv[])
{
	ArgvParser<InputData> parser;

	parser.register_flag_parser("--horiz", display_calendar_horizontal);
	parser.register_flag_parser("--vert", display_calendar_vertical);
	parser.register_flag_parser("--year_once", show_year_once);
	parser.register_flag_parser("--year_for_each_month", show_year_for_each_month);
	parser.register_flag_parser("--year", calendar_for_year);
	parser.register_flag_parser("--month", calendar_for_month);
	parser.register_flag_parser(argv[0], custom_ranged_calendar);

	InputData input = parser.parse_all(argc, argv);
	input.format << input.calendar << std::endl;

	return 0;
}
