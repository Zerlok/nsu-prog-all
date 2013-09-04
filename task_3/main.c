#include "mod.h"
/*
int check_input(int d, int m, int y) {
	if (d > 31 || m > 12 || y > 9999) {
		printf("Invalid date. Use this format: DD/MM/YYYY");
		return 0;
	} else if
*/

int main() {
	int day1, month1, year1, day2, month2, year2;
	scanf("%d/%d/%d", &day1, &month1, &year1);
	scanf("%d/%d/%d", &day2, &month2, &year2);
	printf("------\n");
	//printf("%d\n", get_days(day1, month1, year1));
	//printf("%d\n", get_days(day2, month2, year2));
	printf("%d days\n", get_difference(day1, month1, year1, day2, month2, year2));
	return 0;
}
