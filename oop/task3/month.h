#ifndef __MONTH_H__
#define __MONTH_H__


#include <iostream>
#include <string>
#include <sstream>

#include "date.h"


class Month
{
	public:
		// Constructors / Destructor.
		Month();
		Month(const Month &month);
		Month(const Date &date);

		// Operators.
		Month &operator=(const Month &month);
		Month &operator++(int);
		Month &operator--(int);
		Month operator+(int num) const;
		Month &operator+=(int num);

		bool operator<(int month_num) const { return (_begin.get_month() < month_num); }
		bool operator>(int month_num) const { return (_begin.get_month() > month_num); }
		bool operator<(const Date &date) const { return (_end < date); }
		bool operator>(const Date &date) const { return (_begin > date); }
		bool operator<=(const Date &date) const { return (_end <= date); }
		bool operator>=(const Date &date) const { return (_begin >= date); }
		bool operator<(const Week &week) const { return (_end < week); }
		bool operator>(const Week &week) const { return (_begin > week); }
		bool operator<=(const Week &week) const { return (_end <= week); }
		bool operator>=(const Week &week) const { return (_begin >= week); }

		friend bool operator==(const Month &month1, const Month &month2) { return (month1._begin == month2._begin); }
		friend bool operator!=(const Month &month1, const Month &month2) { return (month1._begin != month2._begin); }
		friend bool operator<(const Month &month1, const Month &month2) { return (month1._begin < month2._begin); }
		friend bool operator>(const Month &month1, const Month &month2) { return (month1._begin > month2._begin); }
		friend bool operator<=(const Month &month1, const Month &month2) { return (month1._begin <= month2._begin); }
		friend bool operator>=(const Month &month1, const Month &month2) { return (month1._begin >= month2._begin); }

		friend std::ostream &operator<<(std::ostream &out, const Month &month);

		// Getters.
		const Date &get_begin() const { return _begin; }
		const Date &get_end() const { return _end; }
		int	get_number() const { return _begin.get_month(); }
		const std::string &get_name() const { return _begin.get_month_name(); }

		int get_year() const { return _begin.get_year(); }

		bool is_contain(const Date &date) { return ((_begin <= date)
													&& (date <= _end)); }
		bool is_contain(const Week &week) { return ((_begin <= week)
													&& (week <= _end)); }

	private:
		// Fields.
		Date _begin;
		Date _end;

		// Methods.
		const Date &get_month_end(const Date &date) const;
};


// Friends.
std::ostream &operator<<(std::ostream &out, const Month &month);


// __MONTH_H__
#endif
