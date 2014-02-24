#include "mod.h"


void print_doc()
/*	Function shows documentation of archivator.	*/
{
	printf("%s - %s\n", ARC_NAME, VERSION);
	printf("You're reading a documentation about %s\n", ARC_NAME);
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
		case ERR_NO_TAG_ARG: printf("Please write arguments after tags!\n"); break;
		default: printf("Unknown error code: %d\n", err_code);
	}
}


void print_tag(char tag[])
/*	
Function simply prints a tag.

Input:
	tag - (*char) the tag.
*/
{
	printf("'%s'\n", tag);
}


int read_tags(int argc, char *argv[])
/*	
Function reads tags from argv and returns zero.
If there are some errors, returns error code.

Input:
	argc - (int) a length of argv,
	argv - (**char) a list of arguments.
*/
{
	int str_indx, arg_indx = 1;
	
	while (arg_indx < argc)
	{
		print_tag(argv[arg_indx]);
		if (!strcmp(argv[arg_indx], FLAG_ADD))
		{
			arg_indx++;
			if(arg_indx + 1 < argc)
			{
				printf("Going append '%s' archive with '%s' file\n", argv[arg_indx], argv[arg_indx + 1]);
			}
			else
			{
				return ERR_NO_TAG_ARG;
			}
		}
		arg_indx++;
	}
	return 0;
}