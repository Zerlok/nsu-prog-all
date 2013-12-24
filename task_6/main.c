#include "mod.h"

int main(int argc, char *argv[]) {
	FILE *input = NULL;
	int i = 0, lst_len = 0, num;
	int *lst = (int*) calloc(lst_len, sizeof(int));

	if (argc > 1) {
		for (i = 1; i < argc; i++) {
			if (!strcmp(argv[i], "-f")) { // If input is name of file with list.
				i += 1; // next element of argv.
				if (i >= argc) {
					printf("ERROR: Please, write the name of file.\n");
					free(lst);
					return 0;
				} else {
					input = fopen(argv[i], "r");

					if(input == NULL) {
						printf("ERROR: file '%s' does not exist!\n", argv[i]);
						free(lst);
						return 0;
					} else {
						while (fscanf(input, "%d ", &num) > 0) {
							lst = (int*) realloc(lst, (i-1) * sizeof(int));
							lst[i - 2] = num;
							i += 1;
						}
						lst_len = i - 2;
					}
					fclose(input);
				}
			} else if (!strcmp(argv[i], "-l")) { // If input is list.
				i += 1; // next element of argv.
				// printf("i: %d; argc: %d; lst_len: %d; argv[i]: '%s'\n", i, argc, lst_len, argv[i]);
				if (i >= argc) {
					printf("ERROR: Please, write elements of array.\n");
					free(lst);
					return 0;
				} else {
					while (i < argc) {
						lst = (int*) realloc(lst, (i-1) * sizeof(int));
						lst[i-2] = atoi(argv[i]);
						i += 1;
					}
					lst_len = i - 2;
				}
			} else { // If input flag wa incorrect.
				printf("ERROR: Please, type a flag\n");
				printf("-l - array\n");
				printf("-f - name of file\n");
				// print_help();
				return 0;
			}
		}
		quick_sort(lst, 0, lst_len - 1);
		print_lst(lst, lst_len);
	} else {
		print_help();
	}
}
