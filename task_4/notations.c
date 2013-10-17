#include "mod.h"

void print_lst(int *l) {
	/*
	Prints array on screen.
	
	Input:
		int *l - array of digits
	Output:
		None
	Notice:
		Array of digits must have value -1 (NUM_END).
	*/
	int i = 1;

	printf("List: [%d", l[0]);
	while (l[i] != NUM_END) {
		printf(", %d", l[i]);
		i += 1;
	}
	printf("]\n");
	printf("Len: %d\n", i);
}

void reverse_lst(int *l) {
	/*
	Revers the array.
	
	Input:
		int *l - array
	Output:
		None
	*/
	int x, i, len = get_len(l);

	for(i = 0; 2 * i < len; i++) {
		x = l[len - i - 1];
		l[len - i - 1] = l[i];
		l[i] = x;
	}
}

void print_help() {
	printf("Input format:\nN b1 b2\nWhere:\nN - number\nb1 - current basement\nb2 - new basement\n");
}

char to_str(int x) {
	if (x >= 0 && x <= 9) {
		return (char)(x + DIGIT_DIFF);
	} else {
		return (char)(x + WORD_DIFF);
	}
}

int get_len(int *lst) {
	/*
	Returns the length of numbers array.
	
	Input:
		int *lst - array of digits
	Output:
		int - length
	Notice:
		Array of digits must have value -1 (NUM_END).
	*/
	int i = 0;

	while (lst[i] != NUM_END) {
		i += 1;
	}
	return i;
}

char to_char_from_int(int x) {
	/*
	Converts char symbol from ASCII code
	and returns it or 0 value if symbol is not a word (A-Z || 0-9).
	
	Input:
		int x - number of symbol in ASCII code
	Output:
		char - symbol
		"0" - if symbol is not a word
	*/
	char chr;

	if (x >= 10 && x <= 37) {
		chr = x + WORD_DIFF;
	} else if (x >= 0 && x <= 9) {
		chr = x + DIGIT_DIFF;
	} else {
		printf("Unknown symbol - %d, %c\n", x, (char)x);
		return 0;
	}
	return chr;
}

char *to_str_from_lst(int *lst) {
	/*
	Converts array of digits to array of symbols and returns the address of this array.
	
	Input:
		int *lst - array of digits
	Output:
		char *str - array of symbols
	Notice:
		Array of digits must have value -1 (NUM_END).
	*/
	static char str[LIMIT];
	int i = 0;

	while (lst[i] != NUM_END) {
		str[i] = to_char_from_int(lst[i]);
		i += 1;
	}
	return str;
}

int to_digit_from_char(char ch) {
	/*
	Converts char symbol to ASCII code number
	and returns it or "0" value if char symbol is not a word (A-z || 0-9).

	Input:
		char ch - symbol
	Ouput:
		int d - ASCII code of symbol
		0 - if ch is not a word
	*/
	int d = toupper(ch);
	// printf("ch = %c\n", ch);

	if (d >= 'A' && d <= 'Z') {
		return d - WORD_DIFF;
	} else if (d >= '0' && d <= '9') {
		return d - DIGIT_DIFF;
	} else {
		printf("Unknown digit - %c\n", d);
		return ERR_DIGIT;
	}
}

int *to_list_from_str(char *num) {
	/*
	Converts array of symbols to array of digits and returns the address of this array.
	
	Input:
		char *str - array of symbols (string)
	Output:
		int *lst - array of digits
	*/
	int i = 0;
	int digit;
	int len = strlen(num);
	static int lst[LIMIT];

	while (i < len) {
		digit = to_digit_from_char(num[i]);
		if (digit != ERR_DIGIT) {
			lst[i] = digit;
		}
		i += 1;
	}
	lst[i] = NUM_END;
	return lst;
}

int check_number_in_notation(int *num, int notation) {
	/*
	Checks is number wrodec in correct notation.

	Input:
		int *num - array of digits
		int notation - notation (basement) of array of digits (number)
	Output:
		int i - index of incorrect digit or
		-1 - if all digits are correct
	Notice:
		Array of digits must have value -1 (NUM_END).
	*/
	int i = 0;

	while (num[i] != NUM_END && num[i] < notation) {
		i += 1;
	}
	if (num[i] == NUM_END) {
		i = NUM_END;
	}
	return i;
}

int *to_notation_from_dec(int num, int notation) {
	/*
	Converts the number in Dec notation to number in given notation.

	Input:
		int num - decimal number
		int notation - basement to convert number
	Output:
		int *new_num - the number array's address
	*/
	static int new_num[LIMIT];
	int i = 0;

	while (num) {
		new_num[i] = num % notation;
		num /= notation;
		i += 1;
	}
	new_num[i] = -1;
	reverse_lst(new_num);
	return new_num;
}

unsigned long long to_dec_from_notation(int *num, int notation) {
	/*
	Converts the number in given notation to dec number.

	Input:
		int *num - array of digits (number)
		int notation - basement of input number
	Output:
		unsigned long long - dec number
	*/
	unsigned long long dec_num = 0;
	int i, len = get_len(num);

	for (i = len - 1; i >= 0; i--) {
		dec_num += num[i] * pow(notation, len - i - 1);
	}
	return dec_num;
}

char *get_number_in_new_notation(char *num, int cur_notation, int new_notation) {
	/*
	Converts the number from current notation to new.
	Returns number in new notation
	or error code if it has a mistakes.

	Input:
		char *num - array of symbols (number in current notation)
		int cur_notation - current notation of number
		int new_notation - new notation of number
	Output:
		char *new_str - array of symbols (number in new notation)
	*/
	int *lst, *new_lst, indx;
	unsigned long long dec;
	
	lst = to_list_from_str(num);
	indx = check_number_in_notation(lst, cur_notation);

	if (cur_notation < MIN_NOTATION) {
		printf("Wrong notation: %d\nWrite notation > 1.\n", cur_notation);
		return NULL;
	} else if (new_notation < MIN_NOTATION) {
		printf("Wrong notation: %d\nWrite notation > 1.\n", new_notation);
		return NULL;
	} else if (indx != NUM_END) {
		printf("Wrong symbol \"%c\" for %d notation.\n", num[indx], cur_notation);
	} else if (cur_notation == new_notation || !lst[0]) {
		return num;
	} else if (lst[0]) {
		dec = to_dec_from_notation(lst, cur_notation);
		new_lst = to_notation_from_dec(dec, new_notation);
		return to_str_from_lst(new_lst);
	}
}
