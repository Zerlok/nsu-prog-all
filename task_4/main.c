#include "mod.h"

int main(int argc, char *argv[]) {
	int cur_notation, new_notation;
	char N[32], *number = N;
	char *new_number;

	// scanf("%s %d %d", number, &cur_notation, &new_notation);
	// printf("OK\n");
	// number = '10';
	// switch (argc) {
	// 	case 1: scanf("%s %d %d", number, &cur_notation, &new_notation); printf("OK\n"); break;
	// 	case 2: number = argv[2];
	// 	case 3: cur_notation = atoi(argv[3]);
	// 	case 4: new_notation = atoi(argv[4]);
	// 	case 2: printf("%s\n", number);
	// 	case 3: printf("%d\n", atoi(cur_notation));
	// 	case 4: printf("%d\n", atoi(new_notation));
	// }
	if (argc == 1) {
		// printf("You work with module notation.c\nType \"--help\" for help\n");
		print_help();
		scanf("%s %d %d", number, &cur_notation, &new_notation);
	}
	// if (argc == 2) {
	// 	if (argv[1] == '--help') {
	// 		print_help();
	// 	}
	// }
	if (argc == 4) {
		number = argv[1];
		cur_notation = atoi(argv[2]);
		new_notation = atoi(argv[3]);
	}
	new_number = get_number_in_new_notation(number, cur_notation, new_notation);
	if (new_number) {
		printf("%s\n", new_number);
	}
	return 0;
}