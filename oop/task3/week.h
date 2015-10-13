#ifndef __WEEK_H__
#define __WEEK_H__


#include <iostream>

#include "date.h"


class Week
{
	public:
		// Static.
		static const int day_width = 4;
		static std::ostream &header(std::ostream &out);

		// Constructors / Destructor.
		Week();
		Week(const Date &date);
		Week(const Date &from, const Date &to);
		Week(const Week &week);
		~Week();

		// Operators.
		Week &operator=(const Week &week);

		Week &operator++(int);
		Week &operator--(int);

		Week operator+(int num);

		bool operator<(const Date &date) { return (_end < date); }
		bool operator>(const Date &date) { return (_begin > date); }
		bool operator<=(const Date &date) { return (_end <= date); }
		bool operator>=(const Date &date) { return (_begin >= date); }

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
		bool is_contain(const Date &date) const { return ((_begin <= date)
														  && (date <= _end)); }

	private:
		// Fields.
		Date _begin;
		Date _end;
};


// Friends.
std::ostream &operator<<(std::ostream &out, const Week &week);


// __WEEK_H__
#endif
