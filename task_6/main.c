#include "mod.h"

int main(int argc, char *argv[]) {
	FILE *input = NULL;
	char *chr=NULL;
	// char *chr;
	// arrayForSort = (int*)realloc( arrayForSort, sizeArrayForSort * sizeof(int) );
	int i = 0, lst_len = 1, num;
	int *lst = (int*) calloc(lst_len, sizeof(int));

	if (lst == NULL) {
		printf("ERROR: Cannot create an array (Memory was not enough)!\n");
		return 0;
	}

	if (argc > 1) {
		for (i = 1; i < argc; i++) {
			if (!strcmp(argv[i], "-f")) {
				if ((i + 1) >= argc) {
					print_help();
					free(lst);
					return 0;
				} else {
					input = fopen(argv[i + 1], "r");

					if(input == NULL) {
						printf("ERROR: file '%s' does not exist!\n", argv[i + 1]);
						free(lst);
						return 0;
					} else {
						while (fscanf(input, "%d ", &num) != EOF) {
							if (i - 1 == lst_len) {
								lst_len += 1;
								lst = (int*) realloc(lst, lst_len * sizeof(int));
							}
							lst[i - 1] = num;
							// printf("'%d'\n", num);
							i += 1;
						}
					}
					fclose(input);
				}
			} else if (argv[i][0] != "-") {
				i += 1;
				printf("i: %d; argc: %d; lst_len: %d; argv[i]: '%s'\n", i, argc, lst_len, argv[i]);
				if (i >= argc) {
					print_help();
					free(lst);
					return 0;
				} else {
					while (i < argc) {
						if (i > lst_len) {
							lst = (int*) realloc(lst, i * sizeof(int));
						}
						printf("i: %d; argc: %d; lst_len: %d; lst[%d] = argv[i]: '%s'\n", i, argc, lst_len, i-2, argv[i]);
						// printf("%s\n", argv[i]);
						lst[i-2] = atoi(argv[i]);
						i += 1;
					}
					lst_len = i;
				}
			} else {
				print_help();
				return 0;
			}
			// if (!strcmp(argv[i], "-l")) {
			// 	if ((i + 1) >= argc) {
			// 		print_help();
			// 		free(lst);
			// 		return 0;
			// 	} else {
			// 		while (i <= argc) {
			// 			if (i == lst_len) {
			// 				lst_len += 10;
			// 				lst = (int*) realloc(lst, lst_len * sizeof(int));
			// 			}
			// 			lst[i] = argv[i];
			// 			i += 1;
			// 		}
			// 	}
			// }
		}
		print_lst(lst, lst_len);
		quick_sort(lst, 0, lst_len - 1);
		print_lst(lst, lst_len);
	} else {
		print_help();
	}
}
