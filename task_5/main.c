#include "mod.h"

int main(int argc, char *argv[]) {
	int *lst;
	int len;

	if (argc != 2) {
		print_help();
	} else {
		len = atoi(argv[1]);
		if (len > 0 && len < 50) {
			lst = range(atoi(argv[1]));
			transpose(lst, 0);
		} else {
			printf("%s\n", ERR_INPUT);
		}
	}
	return 0;
}