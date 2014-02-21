#include "mod.h"


void print_doc()
{
	printf("%s - %s\n", ARC_NAME, VERSION);
	printf("You're reading a documentation about %s\n", ARC_NAME);
}


void print_tag(char tag[])
{
	printf("'%s'\n", tag);
}


int read_tags(int argc, char *argv[])
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
				printf("Going append %s archive with %s file\n", argv[arg_indx], argv[arg_indx + 1]);
			}
			else
			{
				return ERR_NO_ARG;
			}
		}
		arg_indx++;
	}
	return 0;
}