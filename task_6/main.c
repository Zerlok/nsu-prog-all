#include "mod.h"

int main(int argc, char *argv[]) {
	FILE *input = NULL;
	char *chr=NULL;
	// char *chr;
	// arrayForSort = (int*)realloc( arrayForSort, sizeArrayForSort * sizeof(int) );
	int i = 0;
	int *lst = (int*) calloc(LEN, sizeof(int));

	if (lst == NULL) {
		printf("ERROR: Cannot create an array (Memory was not enough)!\n");
		return 0;
	}

	if (argc > 1) {
		for (i = 1; i < argc; i++) {
			if (!strcmp(argv[i], "-i")) {
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
						while (fscanf(input, '%s', chr) != EOF) {
							printf("'%s'\n", chr);
							// fgets(chr);
							i++;
						}
					}
					fclose(input);
				}
			}
		}
	} else {
		print_help();
	}
}
