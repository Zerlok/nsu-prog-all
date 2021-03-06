#include "mod.h"


void print_flag_help()
/*	Function shows help about flags. */
{
	printf("You can use this flags:\n");
	printf("   %s\t\t-\tto add file to archive. \t\t Usage: %s <archive> <file>\n", FLAG_ADD, FLAG_ADD);
	printf("   %s\t\t-\tto extract file from archive. \t\t Usage: %s <archive> <file>\n", FLAG_EXTR, FLAG_EXTR);
	printf("   %s\t\t-\tto get a list of files in archive. \t Usage: %s <archive>\n", FLAG_LIST, FLAG_LIST);
	printf("   %s\t-\tto show this help documentation.\n", FLAG_HELP);
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
	ARCHIVE *archive = (ARCHIVE*)malloc(sizeof(ARCHIVE));
	check_mem(archive, __func__);

	int code = HELP_CODE, indx = 0;

	if (argc > 1)
	{
		code = read_flags(argc, argv);
		indx = code % 10;
		code -= indx;

		switch (code)
		{
			/* Add file to an archive */
			case APPEND_CODE:
			{
				/* Read the archive file */
				switch (read_an_archive(argv[2], archive))
				{
					case 1:
						/* Create an archive if not exist */
						if (create_an_archive(argv[2], archive) != 0)
						{
							printf("The archive '%s' is not exist.\n", argv[2]);
							return 1;
						}
						printf("The new archive was created.\n");
						break;
					case 2:
						printf("The file '%s' is not an archive of %s program.\n", argv[2], ARC_NAME);
						return 1;
				}

				/* Add to the archive */
				switch (add_to_archive(argv[indx], archive))
				{
					case 1:
						printf("The archive '%s' is not exist.\n", argv[2]);
						return 1;
					case 2:
						printf("The file '%s' is not exist.\n", argv[indx]);
						return 1;
					case 3:
						printf("The file '%s' is already added to '%s' archive!\n", argv[indx], argv[2]);
						return 1;
					default:
						printf("The file '%s' added to '%s' archive.\n", argv[indx], argv[2]);
				}

				return 0;
			}

			/* Extract file from the archive */
			case EXTRACT_CODE:
			{
				/* Read the archive file */
				switch (read_an_archive(argv[2], archive))
				{
					case 1:
						printf("The archive '%s' is not exist.\n", argv[2]);
						return 1;
					case 2:
						printf("The file '%s' is not an archive of %s program.\n", argv[2], ARC_NAME);
						return 1;
				}

				/* Extract file */
				switch (extract_file_from_archive(argv[indx], archive))
				{
					case 1:
						printf("The archive '%s' is not exist.\n", argv[2]);
						return 1;
					case 2:
						printf("The file '%s' is not exist.\n", argv[indx]);
						return 1;
					case 3:
						printf("The file '%s' was not found in '%s' archive.\n", argv[indx], argv[2]);
						return 1;
					default:
						printf("The file '%s' was extracted from '%s' archive.\n", argv[indx], argv[2]);
				}

				return 0;
			}

			/* Print the simple list of archived files */
			case LIST_CODE:
			{
				/* Read the archive file */
				switch (read_an_archive(argv[2], archive))
				{
					case 1:
						printf("The archive '%s' is not exist.\n", argv[2]);
						return 1;
					case 2:
						printf("The file '%s' is not an archive of %s program.\n", argv[2], ARC_NAME);
						return 1;
				}

				/* Print the list */
				show_archived_files(archive);
				return 0;
			}

#ifdef DEBUG
			case TESTMODE_CODE:
				run_test(argv[indx + 1], argv[indx]);
				return 0;
#endif
			/* Print the documentation */
			case HELP_CODE:
				print_doc();
				return 0;

			/* Otherwise - bad input */
			default:
			{
				if (code > ERROR_CODE)
				{
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
	/* Documentation */
	{
		print_doc();
	}
	
	return 0;
}
