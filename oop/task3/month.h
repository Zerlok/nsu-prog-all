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
		Month(const Date &date);

		// Operators.
		Month &operator=(const Month &month);
		Month &operator++(int);
		Month &operator--(int);

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
		const std::string &get_name() const { return _begin.get_month_name(); }
		std::string get_header() const;
//		std::string &get_header() const; // : invalid

	private:
		// Fields.
		Date _begin;
		Date _end;

		// Methods.
		const Date &get_month_end(const Date &date) const;
};

std::ostream &operator<<(std::ostream &out, const Month &month);


// __MONTH_H__
#endif
