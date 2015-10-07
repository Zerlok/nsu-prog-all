#ifndef __WEEK_H__
#define __WEEK_H__


#include <iostream>

#include "date.h"


class Week
{
	public:
		static std::ostream &weekday_names(std::ostream &out);

		// Constructors / Destructor.
		Week();
		Week(const Date &date);
		Week(const Date &from, const Date &to);
		Week(const Week &week);
		~Week();

		// Operators.
		Week &operator++(int);
		Week &operator--(int);

		Week &operator=(const Week &week);

		friend bool operator==(const Week &week1, const Week &week2) { return (week1._begin == week2._begin); }
		friend bool operator!=(const Week &week1, const Week &week2) { return (week1._begin != week2._begin); }
		friend bool operator<(const Week &week1, const Week &week2) { return (week1._begin < week2._begin); }
		friend bool operator>(const Week &week1, const Week &week2) { return (week1._begin > week2._begin); }
		friend bool operator<=(const Week &week1, const Week &week2) { return (week1._begin <= week2._begin); }
		friend bool operator>=(const Week &week1, const Week &week2) { return (week1._begin >= week2._begin); }

		friend std::ostream &operator<<(std::ostream &out, const Week &week);

		// Getters.
		const Date &get_begin() const { return _begin; }
		const Date &get_end() const { return _end; }

		bool is_begin(const Date &date) const { return (_begin == date); }
		bool is_end(const Date &date) const	{ return (_end == date);}
		bool is_in(const Date &date) const { return ((_begin <= date)
													 && (date <= _end)); }

	private:
		// Fields.
		Date _begin;
		Date _end;

		static int day_width;
};

std::ostream &operator<<(std::ostream &out, const Week &week);


// __WEEK_H__
#endif
