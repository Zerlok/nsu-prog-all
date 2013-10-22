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

void copy_lst(int *from_lst, int *to_lst) {
	int i = 0;

	while (from_lst[i] != NUM_END) {
		to_lst[i] = from_lst[i];
		i += 1;
	}
	to_lst[i] = NUM_END;
}

int transpose(int *lst, int i) {
	int a, j = i + 1;
	static int trans_lst[LIMIT];

	// if (lst[j] != NUM_END) {
	print_lst(lst);
	// }
	copy_lst(lst, trans_lst);
	while (lst[j] != NUM_END) {
		// trans_lst[i] = lst[j];
		// trans_lst[j] = lst[i];
		// a = trans_lst[i];
		// trans_lst[i] = trans_lst[j];
		// trans_lst[j] = a;
		// copy_lst(trans_lst, lst);
		// transpose(trans_lst, i + 1);
		// a = lst[j];
		// lst[j] = lst[i];
		// lst[i] = a;
		lst[j] = trans_lst[i];
		lst[i] = trans_lst[j];
		transpose(lst, i + 1);
		transpose(lst, j);

		j += 1;
	}
	return i;
}