#include "mod.h"


/* ----- INPUT & OUTPUT ----- */

void print_flag_help()
/*	Function shows help about flags. */
{
	printf("You can use this flags:\n");
	printf("   %s\t\t-\tto add file to archive. \t\t Usage: %s <archive> <file>\n", FLAG_ADD, FLAG_ADD);
	printf("   %s\t\t-\tto extract file from archive. \t\t Usage: %s <archive> <file>\n", FLAG_EXTR, FLAG_EXTR);
	printf("   %s\t\t-\tto get a list of files in archive. \t Usage: %s <archive>\n", FLAG_LIST, FLAG_LIST);
	printf("   %s\t-\tto show this help documentation.\n", FLAG_HELP);

	#ifdef DEBUG
		printf("   %s\t-\tto run test function (FOR DEBUG ONLY!!!).\n", TESTMODE_FLAG);
	#endif
}


void print_doc()
/*	Function shows documentation of archivator.	*/
{
	printf("%s - %s\n", ARC_NAME, ARC_VERSION);
	printf("You're reading a documentation about %s\n", ARC_NAME);
	printf("Archive tag is %s\n", ARC_FILE_TAG);
	printf("Usage: $ harc <flag> <archive> <file>\n");
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
				printf("Unknown error: %d\n", err_code);
			}
			else
			{
				printf("No errors.\n");
			}
			break;
		}
	}
}


int read_flags(int argc, char **argv)
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
		/* Add to archive flag */
		if (!strcmp(argv[arg_indx], FLAG_ADD))
		{
			arg_indx++;
			if(arg_indx + 1 < argc)
			{
				if (!is_an_archive(argv[arg_indx]))
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
		/* Extract from archive flag */
		else if (!strcmp(argv[arg_indx], FLAG_EXTR))
		{
			arg_indx++;
			if(arg_indx + 1 < argc)
			{
				if (!is_an_archive(argv[arg_indx]))
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
		/* List the archived files flag */
		else if (!strcmp(argv[arg_indx], FLAG_LIST))
		{
			if(arg_indx + 1 < argc)
			{
				if (!is_an_archive(argv[arg_indx + 1]))
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
		else if (!strcmp(argv[arg_indx], FLAG_HELP))
		{
			return HELP_CODE;
		}

#ifdef DEBUG
		/* TEST FOR DEBUG ONLY! */
		else if (!strcmp(argv[arg_indx], TESTMODE_FLAG))
		{
			return TESTMODE_CODE + arg_indx + 1;
		}
#endif

		else if (argv[arg_indx][0] == '-')
		{
			return ERR_UNKNOWN_FLAG;
		}

		arg_indx++;
	}
	return ERR_NO_FLAGS + arg_indx;
}


/* ----- ACCESSORY FUNCTIONS ----- */

int get_nums(unsigned long int x)
/*
Counts the digits in number.

Input:
	unsigned long int x - the number.

Output:
	int - counted digits (0 < i < 10).
*/
{
	int n = 10;
	unsigned long int k = 1000000000;

	while (n > 0 && (int)(x / k) == 0)
	{
		if (k != 1)
		{
			k /= 10;
		}
		n--;
	}

	if (n < 1)
	{
		n = 1;
	}

	return n;
}


int is_an_archive(char *file_name)
/*
If file is an archive file returns 0.
Otherwise returns 1.

Input:
	char *file_name - the name of file.
*/
{
	if (!strstr(file_name, ARC_FILE_TAG)) // If not archive file
	{
		/* #TODO: do not skip the '.trarlololo'. '.trar' only! */
		return 1;
	}
	return 0;
}


int is_in_archive(char *file_name, ARCHIVE *archive)
/*
If file is in archive file returns it's number.
Otherwise returns -1.

Input:
	char *file_name - the name of file.
*/
{
	int i = 0;

	/* Check this file in archive */
	while (i < archive->files_count)
	{
		if (!strcmp(file_name, archive->files[i]->name))
		{
			printf("The file '%s' is in '%s' archive.\n", file_name, archive->name);
			return i;
		}

		i++;
	}

	return -1;
}
