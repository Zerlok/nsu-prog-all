#include "mod.h"

int main() { //here is comment
	int day1, month1, year1, day2, month2, year2;

	scanf("%d/%d/%d", &day1, &month1, &year1);
	scanf("%d/%d/%d", &day2, &month2, &year2);
	printf("------\n");

	printf("%d days\n", get_difference(day1, month1, year1, day2, month2, year2) + 1);
	return 0;
}
