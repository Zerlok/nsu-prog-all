#include "mod.h"

int is_valid_date(int d, int m, int y) {
	int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int max_day = months[m - 1];
	if (m == 2) {
		max_day += is_leap_year(y);
	}
	if (d > max_day || m > 12 || y > 9999 || d < 1 || m < 1 || y < 0) {
		printf("Invalid date:\n%d/%d/%d\n", d, m, y);
		return 0;
	}
	return 1;
}

int main() {
	int day1, month1, year1, day2, month2, year2;
	scanf("%d/%d/%d", &day1, &month1, &year1);
	scanf("%d/%d/%d", &day2, &month2, &year2);
	printf("------\n");
	if (is_valid_date(day1, month1, year1) && is_valid_date(day2, month2, year2)) {
		printf("%d days\n", get_difference(day1, month1, year1, day2, month2, year2));
	}
	return 0;
}
