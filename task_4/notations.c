#include "mod.h"

int to_list_from_str(char num[LIMIT]) { //Returns list of digits from string
	int i = 0;
	int len = strlen(num);
	int n;
	int lst[len];
	
	while (i < len) {
		n = toupper(num[i]);
		if (n >= 'A' && n <= 'Z') {
			lst[i] = n - 55;
		} else if (n >= '0' && n <= '9') {
			lst[i] = n - 48;
		}
		printf("%d - %d\n", i, lst[i]);
		i++;
	}
	printf("%d %d\n", *lst, len);
	return lst, len;
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
