#ifndef __DATE_H__
#define __DATE_H__


#include <iostream>


static const int DAYS_IN_MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static const std::string WEEK_DAYS[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};


class Date
{
	public:
		Date();
		Date(int year, int month = 1, int day = 1);
		~Date();

		Date &operator++(int);
		friend long long int operator-(const Date &date1, const Date &date2);
		friend std::ostream &operator<<(std::ostream& out, const Date& date);

		int get_year() const { return _year; }
		int get_month() const { return _month; }
		int get_day() const { return _day; }

		long long int count_days() const;
		int get_weekday_num() const;
		const std::string &get_weekday() const;
		bool is_leap_year() const;

	private:
		int _year;
		int _month;
		int _day;

		bool is_valid() const;
};

long long int operator-(const Date &date1, const Date &date2);
std::ostream& operator<<(std::ostream &out, const Date &date);


// __DATE_H__
#endif
