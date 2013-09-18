#include "mod.h"

void print_lst(int *l, int len) { //Prints values and length of array.
	int i;

	printf("List: [%d", l[0]);
	for (i = 1; i < len; i++) {
		printf(", %d", l[i]);
	}
	printf("]\n");
	printf("Len: %d\n", len);
}

int *to_list_from_str(char *num) {
	/*
	Gets string.
	Returns address of digits array from string.
	*/
	int n, i = 0;
	int len = strlen(num);
	static int lst[LIMIT];

	while (i < len) {
		n = toupper(num[i]);
		if (n >= 'A' && n <= 'Z') {
			lst[i] = n - 55;
		} else if (n >= '0' && n <= '9') {
			lst[i] = n - 48;
		}
		// printf("%d - %d\n", i, lst[i]);
		i += 1;
	}
	// printf("len - %d\n", len);
	return lst;
}

int check_notation(int *num, int len, int notation) {
	/*
	If numbers exsist in notation, returns "-1",
	otherrwise - returns index of wrong number.

	Input: *num, len, notation
	*/
	int i = 0;

	while (i < len && num[i] < notation) {
		i += 1;
	}
	if (i != len) {
		return i;
	} else {
		return -1;
	}
}

int to_notation_from_ten(int *nums, int notation) {
	int new_num = 0;
	
	return new_num;
}

int to_ten_from_notation(int *nums, int notation) {
	int ten_num = 0;
	
	return ten_num;
}

int to_new_notation_from_curr(char *num, int cur_notation, int new_notation) {
	/*
	
	*/
	int new_num = 0;
	int *lst, len, indx;
	
	lst = to_list_from_str(number);
	len = strlen(number);
	indx = check_notation(lst, len, cur_notation);
	if (indx == -1) {
		print_lst(lst, len);
		to_new_notation_from_curr(lst, len);
	} else {
		printf("%d\n", indx);
	}
	return new_num;
}
