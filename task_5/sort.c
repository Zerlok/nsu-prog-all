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

int get_max_indx(int *lst, int i) {
	int max = i;

	i += 1;
	while (lst[i] != NUM_END) {
		if (lst[i] > lst[max]) {
			max = i;
		}
		i += 1;
	}
	return max;
}

int get_min_indx(int *lst, int i) {
	int min = i, j = i;

	i += 1;
	while (lst[i] != NUM_END) {
		if (lst[i] < lst[min]) {
			min = i;
		}
		i += 1;
	}
	return min;
}

void sort(int *lst, int i) {
	int min, max, k = i;

	while (lst[k] != NUM_END) {
		// max = get_max_indx(lst, k);
		// if (k != max) {
		// 	lst[k] += lst[max];
		// 	lst[max] = lst[k] - lst[max];
		// 	lst[k] = lst[k] - lst[max];
		// }
		min = get_min_indx(lst, k);
		if (k != min) {
			lst[k] += lst[min];
			lst[min] = lst[k] - lst[min];
			lst[k] = lst[k] - lst[min];
		}
		k += 1;
	}
}

void swap(int *a, int *b) {
	*a += *b;
	*b = *a - *b;
	*a = *a - *b;
}

int retros(int *lst, int len) {
	int i = len - 1, j = 0;

	while (i >= 0) {
		if (lst[i] < lst[i + 1] && lst[i + 1] != NUM_END) {
			// reverse()
			lst[i] += lst[i + 1];
			lst[i + 1] = lst[i] - lst[i + 1];
			lst[i] = lst[i] - lst[i + 1];
			print_lst(lst);
			sort(lst, i + 1);
		}
		i -= 1;
	}
}

int prostos(int *lst, int a) {
	int i = a;

	if (lst[i] == NUM_END) {
		print_lst(lst);
		// print_lst(lst);
	} else {
		while (lst[i] != NUM_END) {
			// swap(&lst[a], &lst[i]);
			// prostos(lst, i + 1);
			// swap(&lst[a], &lst[i]);
			lst[a] += lst[i];
			lst[i] = lst[a] - lst[i];
			lst[a] = lst[a] - lst[i];
			prostos(lst, i + 1);
			lst[a] += lst[i];
			lst[i] = lst[a] - lst[i];
			lst[a] = lst[a] - lst[i];
			i += 1;
		}
	}
}

int transpose(int *lst, int i) {
	int a, j = i + 1;
	static int trans_lst[LIMIT];

	// if (lst[j] != NUM_END) {
	print_lst(lst);
	// }
	copy_lst(lst, trans_lst);
	// if (lst[j] != NUM_END) {
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
		// transpose(lst, j);

		j += 1;
	}
	return i;
}