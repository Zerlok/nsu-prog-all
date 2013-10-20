#include "mod.h"

int main(int argc, char *argv[]) {
	int *lst;
	int len = argc - 1;

	if (argc == 1) {
		print_help();
	} else {
		// lst = get_lst_from_argv(argc, argv);
		len = atoi(argv[1]);
		lst = range(len);
		reverser(lst, len);
		// print_lst(lst, len);
		// transpose(lst, len);
		// transpose(lst, len);
	}
	return 0;
}