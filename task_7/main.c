#include "mod.h"

int main(int argc, char *argv[]) {
	FILE *input = NULL;
	int i = 0, num;
	struct List *lst = init_list();

	if (argc > 1) {
		for (i = 1; i < argc; i++) {
			if (!strcmp(argv[i], "-f")) {
				i += 1;
				if (i >= argc) {
					print_help();
					delete_list(lst);
					return 0;
				} else {
					input = fopen(argv[i], "r");

					if(input == NULL) {
						printf("ERROR: file '%s' does not exist!\n", argv[i + 1]);
						return 0;
					} else {
						while (fscanf(input, "%d ", &num) > 0) {
							insert(lst, num);
							i += 1;
						}
					}
					fclose(input);
				}
			} else if (!strcmp(argv[i], "-l")) {
				i += 1;
				// printf("i: %d; argc: %d; argv[i]: '%s'\n", i, argc, argv[i]);
				if (i >= argc) {
					print_help();
					delete_list(lst);
					return 0;
				} else {
					while (i < argc) {
						printf("i: %d; argc: %d; lst[%d] = argv[i]: '%s'\n", i, argc, i-2, argv[i]);
						// printf("%s\n", argv[i]);
						insert(lst, atoi(argv[i]));
						i += 1;
					}
				}
			} else {
				print_help();
				return 0;
			}
		}
		print_list(lst);
	} else {
		print_help();
	}
	return 0;
}