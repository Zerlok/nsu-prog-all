#include "mod.h"

int * to_list_from_str(char num[LIMIT]) {
	int i = 0;
	int len = strlen(num);
	int n;
	int *lst[len];
	while (i < len) {
		n = (int)toupper(num[i]);
		if (n > 64 && n < 91) {
			lst[i] = n - 55;
		} else if (n > 47 && n < 58) {
			lst[i] = n - 48;
		}
		printf("%d - %d\n", i, lst[i]);
		i++;
	}
	return lst;
}

int check_notation(int num[LIMIT], int cur_notation) {
	return 1;
}

int to_notation_from_ten(char num[LIMIT], int notation) {
	int new_num = 0;
	return new_num;
}

int to_ten_from_notation(char num[LIMIT], int notation) {
	int ten_num = 0;
	return ten_num;
}

int to_new_from_curr(char num[LIMIT], int cur_notation, int new_notation) {
	int new_num = 0;
	
	return new_num;
}