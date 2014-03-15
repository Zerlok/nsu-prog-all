#include "mod.h"


void print_doc()
/*	Function shows documentation of archivator.	*/
{
	printf("%s - %s\n", ARC_NAME, VERSION);
	printf("You're reading a documentation about %s\n", ARC_NAME);
	printf("Archive tag is %s\n", ARC_FILE_TAG);
	print_flag_help();
}


void print_flag_help()
/*	Function shows help about flags.	*/
{
	printf("You can use this flags:\n");
	printf("   %s\t\t-\tto add file to archive. Usage: %s <file> <archive>\n", FLAG_ADD, FLAG_ADD);
	printf("   %s\t\t-\tto extract file from archive. Usage: %s <file> <archive>\n", FLAG_EXTR, FLAG_EXTR);
	printf("   %s\t\t-\tto get a list of files in archive. Usage: %s <archive>\n", FLAG_LIST, FLAG_LIST);
	printf("   %s\t\t-\tto get a control sum of archive. Usage: %s <archive>\n", FLAG_TEST, FLAG_LIST);
	printf("   %s\t-\tto get a documentation.\n", FLAG_HELP);
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
		case ERR_UNKNOWN_FLAG:
			printf("Please read which flags can be used in help.\n");
			break;
		case ERR_NOT_ARCH_FILE:
			printf("It should be a %s type of archive!\n", ARC_FILE_TAG);
			break;
		default:
			if err_code > ERR_CODE:
				printf("Unknown error (code %d)\n", err_code);
			else:
				printf("No errors.\n");
			break;
	}
}


void print_flag(char flag[])
/*	
Function simply prints a flag.

Input:
	flag - (*char) the flag.
*/
{
	printf("'%s'\n", flag);
}


int is_arch_file(char arg[])
/*
If file is an archive file returns 0.
Otherwise returns 1.

Input:
	arg - (*char) the name of file.
*/
{
	if (!strstr(arg, ARC_FILE_TAG)) // If not archive file
	{
		return 1;
	}
	return 0;
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
	int str_indx, arg_indx = 1;
	
	while (arg_indx < argc)
	{
		if (!strcmp(argv[arg_indx], FLAG_ADD))
		{
			arg_indx++;
			if(arg_indx + 1 < argc)
			{
				if (!is_arch_file(argv[arg_indx + 1]))
				{
					// printf("Going add '%s' file to '%s' archive\n", argv[arg_indx], argv[arg_indx + 1]);
					return APPEND_CODE + arg_indx + 1;
				}
				else
				{
					return ERR_NOT_ARCH_FILE + arg_indx + 1;
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
				if (!is_arch_file(argv[arg_indx + 1]))
				{
					// printf("Going extract '%s' file from '%s' archive\n", argv[arg_indx], argv[arg_indx + 1]);
					return EXTRACT_CODE + arg_indx + 1;
				}
				else
				{
					return ERR_NOT_ARCH_FILE + arg_indx + 1;
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
					// printf("Going show a list of files in '%s' archive\n", argv[arg_indx + 1]);
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
				// printf("Going count a test sum in '%s' archive\n", argv[arg_indx + 1]);
				return TEST_CODE + arg_indx + 1;
			}
			else
			{
				return ERR_NO_FLAG_ARG;
			}
		}
		else if (!strcmp(argv[arg_indx], FLAG_HELP))
		{
			printf("Going show a help\n");
		}
		else if (strstr(argv[arg_indx], "-"))
		{
			print_flag(argv[arg_indx]);
			return ERR_UNKNOWN_FLAG;
		}
		else
		{
			printf("Last arg: '%s'\n", argv[arg_indx]);
		}
		arg_indx++;
	}
	return 0;
}