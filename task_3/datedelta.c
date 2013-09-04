#include "mod.h"

int years_to_days(int year) {
	int highs;
	year--;
	return year / 400 + year / 4 - year / 100 + year * 365;
}

int is_leap_year(int year) {
	if (year % 400 == 0 || year % 100 != 0 && year % 4 == 0) {
		return 1;
	}
	return 0;
}

int months_to_days(int month) {
	int months[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};
	int days = 0;
	month--;
	while (months[month]) {		
		days += months[month];
		month--;
	}
	return days;
}

int get_days(int day, int month, int year) {
	return day + months_to_days(month) + years_to_days(year) + is_leap_year(year);
}

int get_difference(
		int day1, int month1, int year1,
		int day2, int month2, int year2) {
	return abs(get_days(day1, month1, year1) - get_days(day2, month2, year2));
}
