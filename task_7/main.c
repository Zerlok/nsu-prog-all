#include "list.h"

int main(int argc, char *argv[]) {
	int i;
	int array[10] = {12, 32, 434, 0, -12, 23, 34, 1, 12};
	struct List *lst;

	lst = init_list();

	for (i = 0; i < 10; i++) {
		insert(&lst, array[i]);
	}
	print_list(lst);
	return 0;
}