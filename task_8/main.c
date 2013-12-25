#include "mod.h"

int main(int argc, char *argv[]) {
	struct Tree *root = NULL;
	int i = 1;

	if (argc > 1) {
		while (i < argc) {
			// root = stree(root, root, atoi(argv[i]));
			root = insert(root, atoi(argv[i]));
			i += 1;
		}
		print_tree(root);
	} else {
		print_help();
	}
	return 0;
}