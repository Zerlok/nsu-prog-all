#include "mod.h"

void print_lst(int *l, int len) {
	int i;

	printf("List: [%d", l[0]);
	for (i = 1; i < len; i++) {
		printf(", %d", l[i]);
	}
	printf("]\n");
	printf("Len: %d\n", len);
}

void print_error(int err_code, char *msg) {
	switch (err_code) {
		case ERR_UNKNOWN: printf("Unknown error: %s\n", msg);
		case ERR_NOTATION: printf("Wrong notation: %s\n", msg);
		case ERR_SYMBOL: printf("Wrong symbol: %s\n", msg);
		case ERR_DIGIT: printf("Wrong digit: \"%s\"\n", msg);
	}
}

int get_len(int *lst) {
	int i = 0;

	while (lst[i] != NUM_END) {
		i += 1;
	}
	return i;
}

int to_digit_from_char(char ch) {
	int d = toupper(ch);

	if (d >= 'A' && d <= 'Z') {
		return d - 55;
	} else if (d >= '0' && d <= '9') {
		return d - 48;
	} else {
		// print_error(ERR_DIGIT, d);
		printf("Unknown digit - %c\n", d);
		return 0;
	}
}

int *to_list_from_str(char *num) {
	int i = 0;
	int len = strlen(num);
	static int lst[LIMIT];

	while (i < len) {
		lst[i] = to_digit_from_char(num[i]);
		i += 1;
	}
	lst[len] = NUM_END;
	return lst;
}

int check_notation(int *num, int len, int notation) {
	int i = 0;

	while (i < len && num[i] < notation) {
		i += 1;
	}
	if (i == len) {
		i = NUM_END;
	}
	return i;
}

int to_notation_from_ten(int *num, int len, int notation) {
	// int new_num = 0;
	static int new_num[LIMIT];
	int i;


	return new_num;
}

int to_ten_from_notation(int *num, int len, int notation) {
	int ten_num = 0;
	
	return ten_num;
}

int get_number_in_new_notation(char *num, int cur_notation, int new_notation) {
	int new_num = 0;
	int *lst, *ten, len, indx;
	
	lst = to_list_from_str(num);
	len = strlen(num);
	indx = check_notation(lst, len, cur_notation);
	if (indx == NUM_END) {
		ten = to_ten_from_notation(lst, len, cur_notation);
		print_lst(lst, len);
	} else {
		// print_error(ERR_NOTATION, 'index');
		printf("%d\n", indx);
	}
	return new_num;
}
