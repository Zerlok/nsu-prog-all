#include "mod.h"

// #include "debug.h"
#define DEBUG


void print_flag_help()
/*	Function shows help about flags.	*/
{
	// #ifdef DEBUG
	// 	print_func_name(__func__);
	// #endif

	printf("You can use this flags:\n");
	printf("   %s\t\t-\tto add file to archive. \t\t Usage: %s <archive> <file>\n", FLAG_ADD, FLAG_ADD);
	printf("   %s\t\t-\tto extract file from archive. \t\t Usage: %s <archive> <file>\n", FLAG_EXTR, FLAG_EXTR);
	printf("   %s\t\t-\tto get a list of files in archive. \t Usage: %s <archive>\n", FLAG_LIST, FLAG_LIST);
	printf("   %s\t\t-\tto get a control sum of archive. \t Usage: %s <archive>\n", FLAG_TEST, FLAG_TEST);
	printf("   %s\t-\tto show this help documentation.\n", FLAG_HELP);

	#ifdef DEBUG
		printf("   %s\t-\tto run test function (FOR DEBUG ONLY!!!).\n", TESTMODE_FLAG);
		// print_end_func(__func__);
	#endif
}


void print_doc()
/*	Function shows documentation of archivator.	*/
{
	printf("%s - %s\n", ARC_NAME, ARC_VERSION);
	printf("You're reading a documentation about %s\n", ARC_NAME);
	printf("Archive tag is %s\n", ARC_FILE_TAG);
	printf("Using: $ harc <flag> <archive> <file>\n");
	printf("\n");
	print_flag_help();
	printf("\n");
	printf("Examples:\n");
	printf("\t$ harc -a arch.trar file.txt (append arch.trar with file.txt file)\n");
	printf("\t$ harc -l arch.trar (show the list of arch.trar's files)\n");

}


void print_err(int err_code)
/*
Function prints error's messages.

Input:
	err_code - (int) the number of error code.
*/
{
	switch (err_code)
	{
		case ERR_NO_FLAG_ARG:
			printf("Please write arguments after flags!\n");
			print_flag_help();
			break;
		case ERR_NO_FLAGS:
			printf("Please write flags!\n");
			print_flag_help();
			break;
		case ERR_UNKNOWN_FLAG:
			printf("Please read which flags can be used in help.\n");
			print_flag_help();
			break;
		case ERR_NOT_ARCH_FILE:
			printf("Unknown type of archive file!\n");
			printf("It should be a %s type of archive.\n", ARC_FILE_TAG);
			break;
		default:
		{
			if (err_code > ERROR_CODE)
			{
				printf("Unknown error (code %d)\n", err_code);
			}
			else
			{
				printf("No errors.\n");
			}
			break;
		}
	}
}


int read_flags(int argc, char *argv[])
/*
Function reads flags from argv and returns zero.
If there are some errors, returns error code.

Input:
	argc - (int) a length of argv,
	argv - (**char) a list of arguments.
*/
{
	int arg_indx = 1;

	while (arg_indx < argc)
	{
		if (!strcmp(argv[arg_indx], FLAG_ADD))
		{
			arg_indx++;
			if(arg_indx + 1 < argc)
			{
				if (!is_arch_file(argv[arg_indx]))
				{
					return APPEND_CODE + arg_indx + 1;
				}
				else
				{
					return ERR_NOT_ARCH_FILE + arg_indx;
				}
			}
			else
			{
				return ERR_NO_FLAG_ARG + arg_indx - 1;
			}
		}
		else if (!strcmp(argv[arg_indx], FLAG_EXTR))
		{
			arg_indx++;
			if(arg_indx + 1 < argc)
			{
				if (!is_arch_file(argv[arg_indx]))
				{
					return EXTRACT_CODE + arg_indx + 1;
				}
				else
				{
					return ERR_NOT_ARCH_FILE + arg_indx;
				}
			}
			else
			{
				return ERR_NO_FLAG_ARG + arg_indx - 1;
			}
		}
		else if (!strcmp(argv[arg_indx], FLAG_LIST))
		{
			if(arg_indx + 1 < argc)
			{
				if (!is_arch_file(argv[arg_indx + 1]))
				{
					return LIST_CODE + arg_indx + 1;
				}
				else
				{
					return ERR_NOT_ARCH_FILE + arg_indx + 1;
				}
			}
			else
			{
				return ERR_NO_FLAG_ARG + arg_indx;
			}
		}
		else if (!strcmp(argv[arg_indx], FLAG_TEST))
		{
			if(arg_indx + 1 < argc)
			{
				if (!is_arch_file(argv[arg_indx + 1]))
				{
					return TESTSUM_CODE + arg_indx + 1;
				}
				else
				{
					return ERR_NOT_ARCH_FILE + arg_indx + 1;
				}
			}
			else
			{
				return ERR_NO_FLAG_ARG;
			}
		}
		else if (!strcmp(argv[arg_indx], FLAG_HELP))
		{
			return HELP_CODE;
		}

		#ifdef DEBUG
			/*
			FOR DEBUG ONLY!
			*/
			else if (!strcmp(argv[arg_indx], TESTMODE_FLAG))
			{
				return TESTMODE_CODE + arg_indx + 1;
			}
		#endif

		else if (strstr(argv[arg_indx], "-"))
		{
			// print_flag(argv[arg_indx]);
			return ERR_UNKNOWN_FLAG;
		}
		else
		{
			printf("Last arg: '%s'\n", argv[arg_indx]);
		}

		arg_indx++;
	}
	return ERR_NO_FLAGS + arg_indx;
}


int main(int argc, char *argv[])
{
	ARCHIVE *arch = (ARCHIVE*)malloc(sizeof(ARCHIVE));
	int code = HELP_CODE, indx = 0;

	if (argc > 1)
	{
		code = read_flags(argc, argv);
		indx = code % 10;
		code -= indx;
		
		#ifdef DEBUG
			printf("CODE: %d, INDX: %d, ARG: %s\n", code, indx, argv[indx]);
		#endif

		if (code < HELP_CODE)
		{
			read_or_create_an_archive(argv[2], arch);
		}
		printf("Archive name is '%s'\n", arch->name);

		switch (code)
		{
			case APPEND_CODE:
			{
				// printf("Going add '%s' file to '%s' archive\n", argv[arg_indx], argv[arg_indx + 1]);
				if (add_to_archive(argv[indx], arch))
				{
					printf("Something wrong\n");
				}
				else
				{
					write_an_archive_to_file(arch);
					printf("Added!\n");
				}
				break;
			}
			case EXTRACT_CODE:
				printf("Going extract '%s' file from '%s' archive\n", argv[indx-1], argv[indx]);
				break;
			case LIST_CODE:
				printf("Going show a list of files in '%s' archive\n", argv[indx]);
				break;
			case TESTSUM_CODE:
				printf("Going count a test sum in '%s' archive\n", argv[indx]);
				break;
			case TESTMODE_CODE:
				run_test(argv[indx]);
				break;
			case HELP_CODE:
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
	}
	else
	{
		#ifdef DEBUG
			run_test("test/second.txt");
		#else
			print_doc();
		#endif
	}
	
	return 0;
}
