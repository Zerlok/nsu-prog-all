#include "mod.h"

int check_notation(char num[100], int cur_notation) {
	i = 0;
	while (i < strlen(num)) {
		printf("%d, ", num[i]);
		i++;
	}
	return 1;
}

int to_ten_from_high(char num[100], int notation) {
	int ten_num = 0;
	return ten_num;
}

int to_x_from_a(char num[100], int cur_notation, int new_notation) {
	int new_num = 0;
	if (a > 10) {
		to_ten_from_high(num, a);
	} else if (a < 10) {
		printf("a < 10");
	}
	if (x > 10) {
		printf("x < 10");
	} else if (x < 10) {
		printf("x < 10");
	}
	return new_num;
}