#include "mod.h"

void print_help() {
	printf("This module prints all transposes of array\n");
	printf("Type N, where N - number of values in array\n");
	printf("%s\n", ERR_INPUT);
}

/*
	Retruns address of ranged array.
	
	Input:
		int len - length of array
	Output:
		int *lst - address of array
*/
int *range(int len) {
	static int lst[LIMIT];
	int i = 0;

	while (i < LIMIT) {
		lst[i] = NUM_END;
		i += 1;
	}
	i = 0;
	while (i < len) {
		lst[i] = i;
		i += 1;
	}
	return lst;
}

/*
	Prints values of array on screen.
	
	Input:
		int *lst - array of numbers
	Output:
		None
	Notice:
		Array of number must have value -1 (NUM_END).
*/
void print_lst(int *lst) {
	int i = 1;

	printf("[%d", lst[0]);
	while (lst[i] != NUM_END) {
		printf(", %d", lst[i]);
		i += 1;
	}
	printf("]\n");
}

/*
	Changes two values.

	Inpput:
		int *a - address of first value
		int *b - address of second value
	Output:
		None
*/
void swap(int *a, int *b) {
	int v = *a;

	*a = *b;
	*b = v;
}

/*
	Generates and prints transposes of array.

	Input:
		int *lst - array of numbers
		int a - index of begin
	Output:
		None
*/
void transpose(int *lst, int a) {
	int i = a;

	if (lst[a] == NUM_END) {
		print_lst(lst);
	} else {
		while (lst[i] != NUM_END) {
			swap(&lst[a], &lst[i]);
			transpose(lst, a + 1);
			swap(&lst[a], &lst[i]);
			i += 1;
		}
	}
}