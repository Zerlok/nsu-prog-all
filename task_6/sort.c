#include "mod.h"

/*
	Prints help.
*/
void print_help() {
	printf("Type array. Please, separate elements with space: A1 A2 A3 ... An\n");
	printf("All elements must be integer. n: 0 < n < %d\n", LIMIT);
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
void print_lst(int *lst, int len) {
	int i = 1;

	printf("[%d", lst[0]);
	while (i < len) {
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
	int c = *a;

	*a = *b;
	*b = c;
}

/*
	Gets array from argv and returns it's address.

	Input:
		char *argv - address of argv
		int len - length of array
	Output:
		int lst - address of array
*/
int get_lst_from_argv(char *argv, int len) {
	static int lst[LIMIT];
	int i = 1;

	while (i < len) {
		printf("%d ", atoi(&argv[i]));
		lst[i] = argv[i];
		i += 1;
	}
	return lst;
}

void quick_sort(int *lst, int l, int r) {
	int i = l, j = r, mid = (l + r) / 2;

	while (i <= j) {
		while (lst[i] < lst[mid]) i += 1;
		while (lst[j] > lst[mid]) j -= 1;
		if (i <= j) {
			swap(&lst[i], &lst[j]);
			i += 1;
			j -= 1;
		}
	}
	if (l < j) {
		quick_sort(lst, l, j);
	}
	if (i < r) {
		quick_sort(lst, i, r);
	}
	
}