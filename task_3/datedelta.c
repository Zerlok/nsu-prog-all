#include "mod.h"

int is_leap_year(int year) {
	if (year % 400 == 0 || year % 100 != 0 && year % 4 == 0) {
		return 1;
	}
	return 0;
}

int is_valid_date(int d, int m, int y) {
	int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //List of month's days
	int max_day = months[m - 1]; //Max days in current month
	
	if (m == 2 && is_leap_year(y)) {
		max_day += 1;
	}
	if (d > max_day || m > 12 || y > 9999 || d < 1 || m < 1 || y < 0) {
		printf("Invalid date:\n%d/%d/%d\n", d, m, y);
		return 0;
	}
	return 1;
}

int years_to_days(int year) {
	year--; //Except current year
	return year / 400 + year / 4 - year / 100 + year * 365; //years * 365 + leap-years
}

int months_to_days(int month, int year) {
	int months[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30}; //List of month's days (except december)
	int days = 0;
	month--; //Except current month

	while (months[month]) {		
		days += months[month];
		if (month == 2 && is_leap_year(year)) {
			days += 1;
		}
		month--;
	}
	return days;
}

int get_days(int day, int month, int year) { //Converts Date to days
	return day + months_to_days(month, year) + years_to_days(year);
}

int get_difference(
		int day1, int month1, int year1,
		int day2, int month2, int year2) {
	if (is_valid_date(day1, month1, year1) && is_valid_date(day2, month2, year2)) {
		return abs(get_days(day1, month1, year1) - get_days(day2, month2, year2));
	}
	return 0;
}
