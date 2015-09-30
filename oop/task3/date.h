#ifndef __DATE_H__
#define __DATE_H__


#include <iostream>


class Date
{
	public:
		Date();
		Date(int year, int month = 1, int day = 1);
		~Date();

		friend std::ostream& operator<<(std::ostream& out, const Date& date);

		int get_year() const { return _year; }
		int get_month() const { return _month; }
		int get_day() const { return _day; }

	private:
		int _year;
		int _month;
		int _day;
};

std::ostream& operator<<(std::ostream &out, const Date &date);



// __DATE_H__
#endif
