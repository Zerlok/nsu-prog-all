#include "mod.h"

List {
	List *next = LIST_END;
	int value = 0;
};

void free_list(List *head) {
	List *nxt;

	while (head) {
		nxt = head -> next;
		free(head);
		head = nxt;
	}
}

int add_new(List *head, int val) {
	List *last = head;

	while (head -> next) {

	}
}

void print_help() {
	printf("This is list module on C.\n");
	printf("Input:\n");
	printf("[a1,a2,a3,a4,...aN] a\n");
	printf("Where [a1,...aN] - List\n");
	printf("a - new element\n");
}