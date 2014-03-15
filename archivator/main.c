#include "mod.h"


int main(int argc, char *argv[])
{
	int code, indx;

	printf("-------------------\n");
	if (argc > 1)
	{
		code = read_flags(argc, argv);
		indx = code % 10;
		if (code > ERROR_CODE)
		{
			printf("Program was stopped with error code %d\n", code);
			print_err(code - indx);
		}
		else if (code > 0 && indx)
		{
			printf("Gonna work...\n");
			printf("CODE: %d, INDX: %d, ARG: %s\n", code, indx, argv[indx]);
		}
	}
	else
	{
		print_doc();
	}
	printf("-------------------\n");
	return 0;
}