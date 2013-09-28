#include "mod.h"

void print_lst(int *l) {
	int i = 1;

	printf("List: [%d", l[0]);
	while (l[i] != NUM_END) {
		printf(", %d", l[i]);
		i += 1;
	}
	printf("]\n");
	printf("Len: %d\n", i);
}

void print_error(int err_code, char *msg) {
	switch (err_code) {
		case ERR_UNKNOWN: printf("Unknown error:\n\t%s\n", msg);
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
		return d - WORD_DIFF;
	} else if (d >= '0' && d <= '9') {
		return d - DIGIT_DIFF;
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

int check_notation(int *num, int notation) {
	int i = 0;

	while (num[i] != NUM_END && num[i] < notation) {
		i += 1;
	}
	if (num[i] == NUM_END) {
		i = NUM_END;
	}
	return i;
}

int to_notation_from_ten(int *num, int notation) {
	// int new_num = 0;
	static int new_num[LIMIT];
	int i;


	return new_num;
}

int to_ten_from_notation(int *num, int notation) {
	int ten_num = 0;
	
	return ten_num;
}

int get_number_in_new_notation(char *num, int cur_notation, int new_notation) {
	int *lst, *ten, *new_lst, indx;
	
	lst = to_list_from_str(num);
	indx = check_notation(lst, cur_notation);
	if (indx != NUM_END) {
		// print_error(ERR_NOTATION, 'index');
		printf("%d\n", indx);
	} else if (cur_notation == new_notation) {
		print_lst(lst);
	} else {
		ten = to_ten_from_notation(lst, cur_notation);
		print_lst(lst);
	}
	return new_num;
}
