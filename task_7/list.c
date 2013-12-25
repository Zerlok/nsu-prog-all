#include "mod.h"

void print_help() {
	printf("This is list module on C.\n");
	printf("Elements of list must be separated by space.\n");
	printf("Example: A1 A2 A3 ... An\n");
	printf("Flags:\n");
	printf("   -l - list\n");
}

struct List *init_list() {
	struct List * list = (struct List*) malloc (sizeof(struct List));

	list = NULL;
	return list;
}

void print_list(struct List *list) {
	struct List * nxt_lst = list;

	printf("[");
	while (nxt_lst) {
		printf("%d ", nxt_lst->value);
		nxt_lst = nxt_lst->next;
	}
	printf("]\n");
}

void delete_list(struct List *list) {
	struct List *lst = list, *nxt;

	while (lst) {
		nxt = lst->next;
		free(lst);
		lst = nxt;
	}
}

int insert(struct List **list, int value) {
	struct List *last_list, *next_list = (*list);
	struct List *lst = (struct List*) malloc(sizeof(struct List));
	
	// if (list == NULL)
	// 	return 1;

	lst->value = value;
	lst->next = NULL;

	if (next_list == NULL) {
		(*list) = lst;
		return 0;
	}

	if (lst->value < next_list->value) {
		lst->next = next_list;
		(*list) = lst;
		return 0;
	}

	last_list = next_list;
	next_list = next_list->next;

	while (next_list) {
		if (lst->value < next_list->value) {
			last_list->next = lst;
			lst->next = next_list;
			return 0;
		}
		last_list = next_list;
		next_list = next_list->next;
	}
	// last_list->next = lst;
	return 0;
}
