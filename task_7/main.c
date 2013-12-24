#include "list.h"

int main(int argc, char *argv[]) {
	FILE *input = NULL;
	int i = 1, num;
	struct List *lst;

	lst = init_list();

	if (argc > 1) {
		for (i = 1; i < argc; i++) {
			if (!strcmp(argv[i], "-f")) {
				if ((i + 1) >= argc) {
					print_help();
					return 0;
				} else {
					input = fopen(argv[i + 1], "r");

					if(input == NULL) {
						printf("ERROR: file '%s' does not exist!\n", argv[i + 1]);
						return 0;
					} else {
						while (fscanf(input, "%d ", &num) != EOF) {
							insert(lst, num);
							i += 1;
						}
					}
					fclose(input);
				}
			} else if (argv[i][0] != "-") {
				i += 1;
				printf("i: %d; argc: %d; argv[i]: '%s'\n", i, argc, argv[i]);
				if (i >= argc) {
					print_help();
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