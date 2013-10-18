#include "mod.h"

void print_help() {
	printf("Sort - C module. Author - Zerlok\n");
}

int *range(int len) {
	/*
	Retruns address of ranged array.
	
	Input:
		int len - length of array
	Output:
		int *lst - address of array
	*/
	static int lst[LIMIT];
	int i;

	for (i = 0; i < len; i++) {
		lst[i] = i;
	}
	lst[len] = NUM_END;
	return lst;
}

void print_lst(int *lst) {
	/*
	Prints values of array on screen.
	
	Input:
		int *lst - array of numbers
	Output:
		None
	Notice:
		Array of number must have value -1 (NUM_END).
	*/
	int i = 1;

	printf("[%d", lst[0]);
	// for (i = 1; i < len; i++) {
	// 	printf(", %d", lst[i]);
	// }
	while (lst[i] != NUM_END) {
		printf(", %d", lst[i]);
		i += 1;
	}
	printf("]\n");
	// printf("Len: %d\n", i);
}

int get_len(int *lst) {
	int i = 0;

	while (lst[i] != NUM_END && i < LIMIT) i += 1;
	return i;
}

int *get_lst_from_argv(int len, int *argv) {
	static int lst[LIMIT];
	int i = 1;

	while (i < len) {
		lst[i - 1] = argv[i];
		i += 1;
	}
	return lst;
}

int transpose(int *lst, int i) {
	int j = i;
	// int len = get_len(lst);

	while (i > 1 && lst[i] != NUM_END) {
	// if (i > 1) {
		// printf("Before:");
		// print_lst(lst);
		lst[i - 1] += lst[i - 2];
		lst[i - 2] = lst[i - 1] - lst[i - 2];
		lst[i - 1] = lst[i - 1] - lst[i - 2];
		// printf("After:");
		print_lst(lst);
		i += 1;
		// print_lst(lst);
		// transpose(lst, i);
	}
	printf("%d %d\n", j, i);
	if (j > 1) {
		transpose(lst, j - 1);
	}
	return 0;
}