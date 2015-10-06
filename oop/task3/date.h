#ifndef __DATE_H__
#define __DATE_H__


#include <iostream>


static const int DAYS_IN_MONTH[12] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};
static const std::string MONTH_NAMES[12] = {
	"January", "February", "March", "April", "May", "June", "July", "August",
	"September", "October", "November", "December"
};
static const std::string WEEKDAY_NAMES[7] = {
	"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
};


class Date
{
	public:
		Date();
		Date(const Date &date);
		Date(int year, int month = 1, int day = 1);
		~Date();

		Date &operator=(const Date &date);

		Date &operator++(int);
		Date &operator--(int);

		friend Date &operator+(const Date &date, int days);
		friend Date &operator-(const Date &date, int days);
		friend long long int operator-(const Date &date1, const Date &date2);

		friend bool operator==(const Date &date1, const Date &date2) { return (date1._days_num == date2._days_num); }
		friend bool operator<(const Date &date1, const Date &date2) { return (date1._days_num < date2._days_num); }
		friend bool operator>(const Date &date1, const Date &date2) { return (date1._days_num > date2._days_num); }
		friend bool operator<=(const Date &date1, const Date &date2) { return ((date1 < date2) || (date1 == date2)); }
		friend bool operator>=(const Date &date1, const Date &date2) { return ((date1 > date2) || (date1 == date2)); }

		friend std::ostream &operator<<(std::ostream& out, const Date& date);

		int get_year() const { return _year; }
		int get_month() const { return _month; }
		int get_day() const { return _day; }
		int get_weekday() const { return _days_num % 7; }
		long long int to_days() const { return _days_num; }

		const std::string &get_month_name() const { return MONTH_NAMES[_month-1]; }
		const std::string &get_weekday_name() const { return WEEKDAY_NAMES[get_weekday()]; }

		bool is_leap_year() const;

		void add_week();
		void add_month();
		void sub_week();
		void sub_month();

	private:
		int _year;
		int _month;
		int _day;
		long long int _days_num;

		bool is_valid() const;

		int get_days_in_month(int diff = 0) const;
		long long int count_days() const;
};

Date &operator+(const Date &date, int days);
Date &operator-(const Date &date, int days);
long long int operator-(const Date &date1, const Date &date2);

std::ostream &operator<<(std::ostream &out, const Date &date);


// __DATE_H__
#endif
