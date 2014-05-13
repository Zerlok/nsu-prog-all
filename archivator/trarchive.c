#include "mod.h"


/* ---------- DEBUG FUNCTIONS ---------- */
#ifdef DEBUG


void print_func_name(const char name[])
{
	printf("\n>-----RUN----->\t'%s' function:\n", name);
}

void print_end_func(const char name[])
{
	printf("\n<-----END-----<\t'%s' function:\n", name);
}

void print_decor()
/*
Prints decorating symbols in output.
*/
{
	printf("+++++++++++++++++++++++++\n");
}


void decorate(char str[])
/*
Prints char symbols in decorating view.
*/
{
	print_decor();
	printf("+\n");
	printf("+ %12s\n", str);
	printf("+\n");
	print_decor();
	// printf("\n");
}


int run_test(char *file_name)
{
	#ifdef DEBUG
		print_func_name(__func__);
	#endif

	print_bin_file(file_name);

	#ifdef DEBUG
		print_end_func(__func__);
	#endif

	return 0;
}


#endif


/* ---------- ACCESSORY FUNCTIONS ---------- */

void print_doc()
/*	Function shows documentation of archivator.	*/
{
	#ifdef DEBUG
		print_func_name(__func__);
	#endif
	
	printf("%s - %s\n", ARC_NAME, ARC_VERSION);
	printf("You're reading a documentation about %s\n", ARC_NAME);
	printf("Archive tag is %s\n", ARC_FILE_TAG);
	printf("Using: $ harc <flag> <file> <archive>\n");
	printf("\n");
	print_flag_help();
	printf("\n");
	printf("Examples:\n");
	printf("\t$ harc -a file.txt arch.trar (append arch.trar with file.txt file)\n");
	printf("\t$ harc -l arch.trar (show the list of arch.trar's files)\n");
	
	#ifdef DEBUG
		print_end_func(__func__);
	#endif
}


void print_flag_help()
/*	Function shows help about flags.	*/
{
	// #ifdef DEBUG
	// 	print_func_name(__func__);
	// #endif
	
	printf("You can use this flags:\n");
	printf("   %s\t\t-\tto add file to archive. \t\t Usage: %s <file> <archive>\n", FLAG_ADD, FLAG_ADD);
	printf("   %s\t\t-\tto extract file from archive. \t\t Usage: %s <file> <archive>\n", FLAG_EXTR, FLAG_EXTR);
	printf("   %s\t\t-\tto get a list of files in archive. \t Usage: %s <archive>\n", FLAG_LIST, FLAG_LIST);
	printf("   %s\t\t-\tto get a control sum of archive. \t Usage: %s <archive>\n", FLAG_TEST, FLAG_TEST);
	printf("   %s\t-\tto show this help documentation.\n", FLAG_HELP);
	
	#ifdef DEBUG
		printf("   %s\t-\tto run test function (FOR DEBUG ONLY!!!).\n", TESTMODE_FLAG);
		// print_end_func(__func__);
	#endif
}


void print_err(int err_code)
/*
Function prints error's messages.

Input:
	err_code - (int) the number of error code.
*/
{
	#ifdef DEBUG
		print_func_name(__func__);
	#endif

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

	#ifdef DEBUG
		print_end_func(__func__);
	#endif
}


int is_arch_file(char arg[])
/*
If file is an archive file returns 0.
Otherwise returns 1.
Input:
	arg - (*char) the name of file.
*/
{
	#ifdef DEBUG
		print_func_name(__func__);
	#endif
	
	if (!strstr(arg, ARC_FILE_TAG)) // If not archive file
		/* TODO: do not skip the '.trarlololo'. '.trar' only! */
	{
		return 1;
	}

	#ifdef DEBUG
		print_end_func(__func__);
	#endif

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
	#ifdef DEBUG
		print_func_name(__func__);
	#endif

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


int read_or_create_an_archive(char *arch_name, ARCHIVE *arch)
/*
Read the archive information to ARCHIVE structure, if archive exist.
Otherwise create the archive struct with basic information.

Input:
	char *arch_name - the name of file
	ARCHIVE *arch - the indicator to archive struct.

Output:
	Return 0 if everything is OK, else 1.
*/
{
	#ifdef DEBUG
		print_func_name(__func__);
	#endif

	FILE *arch_file;
	struct stat file_status;
	char line[256];
	int i = 0;

	if (is_arch_file(arch_name))
	{
		printf("The file '%s' is not an archive of %s program.\n", arch_name, ARC_NAME);
		exit(1);
	}
	if (stat(arch_name, &file_status) < 0)
	{
		printf("Permission denied to the archive '%s'\n", arch_name);
		exit(1);
	}

	strcpy(arch->name, arch_name);
	if ((arch_file = fopen(arch_name, "r")) == NULL)
	{
		/* CREATE THE ARCHIVE */
		printf("created : arch->name == '%s'\n", arch->name);
		strcpy(arch->files[0], "");
		strcpy(arch->version, ARC_VERSION);
		return 0;
		// fprintf(arch_file, "%s {\n\n}\n", FILES_TAG);
		// arch->last_file = ftell(arch_file) - 2;
		// fprintf(arch_file, "%s { %s }\n", VERSION_TAG, ARC_VERSION);
	}

	/* IF ARCHIVE EXIST: */
	strcpy(arch->name, arch_name);
	while (fscanf(arch_file, "%s {\n", line) != EOF)
	{
		// printf("'%s'\n", line);
		if (strcmp(line, FILES_TAG) == 0)
		{
			// arch->files = (char **)malloc(sizeof(char));
			/* Malloc doesn't work. Of course it's my mistake.*/
			
			while ((fscanf(arch_file, "%s\n", line) != EOF)
				&& (strcmp(line, "}") != 0))
			{
				strcpy(arch->files[i], line);
				i += 1;
			}
			// arch->last_file = ftell(arch_file) - 1;
		}
		else if (strcmp(line, VERSION_TAG) == 0)
		{
			fscanf(arch_file, "%s", arch->version);
			if (strcmp(arch->version, ARC_VERSION) != 0)
			{
				printf("'%s'\n'%s'\n", arch->version, ARC_VERSION);
				return ERR_UNSUPPORTED_VERSION;
			}
		}
		else if (strcmp(line, TREE_TAG) == 0)
		{
			printf("Tree doesn't supported!\n");
		}
	}
	printf("exist : arch->name == '%s'\n", arch->name);
	
	#ifdef DEBUG
		print_end_func(__func__);
	#endif

	return 0;
}


/* ---------- ARCHIVE FUNCTIONS ---------- */


void print_bin_file(char *file_name)
{
	#ifdef DEBUG
		print_func_name(__func__);
	#endif

	FILE *file;
	unsigned char str;
    int i = 1;

	if((file = fopen(file_name, "rb")) == NULL)
	{
		printf("Error while file opening!\n");
		exit(1);
	}

    printf("The content of '%s' file:\n", file_name);
	while (fread(&str, sizeof(str), 1, file))
    {
         printf("%02x", str);
         if (!(i % 2)) printf(" ");
         if (!(i % 16)) printf("\n");
         i++;
	}

	fclose(file);
	
	#ifdef DEBUG
		print_end_func(__func__);
	#endif
}


int add_to_archive(char *file_name, ARCHIVE *arch)
{
	#ifdef DEBUG
		print_func_name(__func__);
	#endif

	int i = 0, is_added = 0;
	struct stat file_status;
	
	if (stat(file_name, &file_status) < 0)
	{
		printf("Permission denied to the archive '%s'\n", file_name);
		exit(1);
	}

	if (strcmp(arch->name, file_name) == 0)
	{
		printf("Are you stupid?\n");
		return 0;
	}

	while (strlen(arch->files[i]) != 0)
	{
		if (strcmp(arch->files[i], file_name) == 0)
		{
			is_added = 1;
		}
		i += 1;
	}

	if (is_added == 1)
	{
		printf("File exist in archive, update it?\n");
	}
	else
	{
		// fprintf(arch_file, "%s\n", file_name);
		printf("arch->files[%d] = '%s'\n", i, file_name);
		strcpy(arch->files[i], file_name);
	}

	#ifdef DEBUG
		print_end_func(__func__);
	#endif

	return 0;
}


int show_archived_files(ARCHIVE *arch)
{
	#ifdef DEBUG
		print_func_name(__func__);
	#endif

	int i = 0;
	
	printf("Archive: '%s'\n", arch->name);
	while (strlen(arch->files[i]) != 0 && i < 256)
	{
		printf("   |---'%s'\n", arch->files[i]);
		i += 1;
	}
	printf("------\nTotal: %d files.\n", i);

	#ifdef DEBUG
		print_end_func(__func__);
	#endif

	return 0;
}


int write_an_archive_to_file(ARCHIVE *arch)
{
	#ifdef DEBUG
		print_func_name(__func__);
	#endif

	FILE *arch_file;
	int i = 0;
	struct stat file_status;
	
	if (stat(arch->name, &file_status) < 0)
	{
		printf("Permission denied to the archive '%s'\n", arch->name);
		exit(1);
	}

	if ((arch_file = fopen(arch->name, "w")) != NULL)
	{
		printf("EXCEPTION!\n");
		exit(1);
	}

	fprintf(arch_file, "%s { %s }\n", VERSION_TAG, arch->version);

	fprintf(arch_file, "%s {\n", FILES_TAG);
	while (strlen(arch->files[i]) != 0 && i < 256)
	{
		fprintf(arch_file, "%s\n", arch->files[i]);
		i += 1;
	}
	fprintf(arch_file, "}\n");
	
	#ifdef DEBUG
		print_end_func(__func__);
	#endif

	return 0;
}
