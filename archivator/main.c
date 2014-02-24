#include "mod.h"


int main(int argc, char *argv[])
{
	int err_code = 0;

	if (argc > 1)
	{
		err_code = read_tags(argc, argv);
		if (err_code)
		{
			printf("Program was stopped with error code %d\n", err_code);
			print_err(err_code);
		}
	}
	else
	{
		print_doc();
	}
	return 0;
}