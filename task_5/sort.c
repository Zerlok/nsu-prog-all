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

int reverser(int *lst, int len) {
	// int j, a, i = len;
	int j, a, i = 0;

	// while (i > 0) {
	// 	// j = i + 1;
	// 	j = len - 1;
	// 	while (j >= 1) {
	// 		a = lst[j - 1];
	// 		lst[j - 1] = lst[j];
	// 		lst[j] = a;
	// 		print_lst(lst);
	// 		j -= 1;
	// 	}
	// 	i -= 1;
	// }
	while (i < len) {
		// j = i + 1;
		j = 0;
		while (j < len - 1) {
			a = lst[j + 1];
			lst[j + 1] = lst[j];
			lst[j] = a;
			print_lst(lst);
			j += 1;
		}
		i += 1;
	}
}

int transpose(int *lst, int j) {
	int i = j - 1;
	int trans_lst[LIMIT];
	// int len = get_len(lst);

	j -= 1;
	copy_lst(lst, trans_lst);
	printf(" = %d\n", j);
	// while (i > 1 && trans_lst[i - 1] != NUM_END) {
	if (i > 1 && trans_lst[i - 1] != NUM_END) {
		trans_lst[i - 1] += trans_lst[i - 2];
		trans_lst[i - 2] = trans_lst[i - 1] - trans_lst[i - 2];
		trans_lst[i - 1] = trans_lst[i - 1] - trans_lst[i - 2];
		print_lst(trans_lst);
		// if (trans_lst[j + 2] != NUM_END) {
		transpose(lst, j + 1);
		transpose(trans_lst, i + 1);
		// }
		i -= 1;
		// printf("i: %d | j: %d\n", i, j);
	}
	// printf("----------\n");
	// if (i > 1) {
	// 	transpose(lst, i + 1);
	// }
	// printf("Was: ");
	// print_lst(lst);
	// printf("i: %d | j: %d\n", i, j);
	// if (j > 1) {
	// 	print_lst(trans_lst);
	// }
	return 0;
}