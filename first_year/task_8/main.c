#include "mod.h"

int main(int argc, char *argv[]) {
	struct Tree *root = NULL;
	int i = 1;

	if (argc > 1) {
		while (i < argc) {
			root = insert(root, atoi(argv[i]));
			i += 1;
		}
		print_tree(root);
	} else {
		print_help();
	}
	printf("\n");
	return 0;
}