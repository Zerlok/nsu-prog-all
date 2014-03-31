#include "mod.h"


int main(int argc, char *argv[])
{
	int code=HELP_CODE, indx=0;

	#ifdef DEBUG
		// decorate("DEBUG is TRUE\n");
		// print_func_name("main");
	#endif

	if (argc > 1)
	{
		code = read_flags(argc, argv);
		indx = code % 10;
		code -= indx;
		
		#ifdef DEBUG
			print_end_func("read_flags");
			printf("CODE: %d, INDX: %d, ARG: %s\n", code, indx, argv[indx]);
		#endif

		switch (code)
		{
			case APPEND_CODE:
				// printf("Going add '%s' file to '%s' archive\n", argv[arg_indx], argv[arg_indx + 1]);
				break;
			case EXTRACT_CODE:
				// printf("Going extract '%s' file from '%s' archive\n", argv[arg_indx], argv[arg_indx + 1]);
				break;
			case LIST_CODE:
				// printf("Going show a list of files in '%s' archive\n", argv[arg_indx + 1]);
				break;
			case TESTSUM_CODE:
				// printf("Going count a test sum in '%s' archive\n", argv[arg_indx + 1]);
				break;
			case TESTMODE_CODE:
				run_test(argv[indx]);
				break;
			case HELP_CODE:
				// printf("Going show a help\n");
				print_doc();
				break;
			default:
			{
				if (code > ERROR_CODE)
				{
					printf("Program was stopped with error code %d\n", code);
					print_err(code);
				}
				else
				{
					printf("Program stopped with unknown code: %d\n", code);
				}
				return 1;
			}
		}
		// }
	}
	else
	{
		#ifdef DEBUG
			run_test("_test/image.png");
		#else
			print_doc();
		#endif
	}

	#ifdef DEBUG
		// print_end_func("main");
	#endif

	return 0;
}