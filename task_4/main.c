#include "mod.h"

int main(int argc, char *argv[]) {
	int cur_notation, new_notation;
	char N[32], *number = N;
	char *new_number;

	if (argc == 4) {
		number = argv[1];
		cur_notation = atoi(argv[2]);
		new_notation = atoi(argv[3]);
		new_number = get_number_in_new_notation(number, cur_notation, new_notation);
		if (new_number) {
			printf("%s\n", new_number);
		}
	} else {
		print_help();
	}
	return 0;
}