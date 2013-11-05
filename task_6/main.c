#include "mod.h"

int main(int argc, char *argv[]) {
	int lst[LIMIT];
	int i = 0, len = argc - 1;
	
	if (len > 0 && len < LIMIT) {
		// Scan argv into array
		while (i < len) {
			lst[i] = atoi(argv[i+1]);
			i += 1;
		}
		print_lst(lst, len);
		quick_sort(lst, 0, len);
		print_lst(lst, len);
	} else {
		print_help();
	}
	return 0;
}