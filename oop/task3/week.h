#ifndef __WEEK_H__
#define __WEEK_H__


#include "date.h"


class Week
{
	public:
		Week(const Date &date);
		Week(const Date &from, const Date &to);

	private:
		Date _begin;
		Date _end;
};


// __WEEK_H__
#endif
