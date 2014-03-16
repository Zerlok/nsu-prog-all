#include "mod.h"


int main(int argc, char *argv[])
{
	int code=HELP_CODE, indx=0;

	#ifdef DEBUG
	printf("DEBUG is TRUE\n");
	#endif

	if (argc > 1)
	{
		code = read_flags(argc, argv);
		indx = code % 10;
		// if (code > 0 && indx)
		// {
		printf("Gonna work...\n");
		printf("CODE: %d, INDX: %d, ARG: %s\n", code, indx, argv[indx]);
		switch (code)
		{
			case APPEND_CODE:
				break;
			case EXTRACT_CODE:
				break;
			default:
			{
				if (code > ERROR_CODE)
				{
					printf("Program was stopped with error code %d\n", code);
					print_err(code - indx);
				}
				else
				{
					printf("Program stopped with unknown code: %d\n", code);
				}
			}
		}
		// }
	}
	else
	{
		print_doc();
	}
	return 0;
}