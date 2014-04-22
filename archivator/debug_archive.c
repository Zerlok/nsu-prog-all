/* ---------- DEBUG FUNCTIONS ---------- */


void print_flag(char flag[])
/*	
Function simply prints a flag.

Input:
	flag - (*char) the flag.
*/
{
	printf("flag : '%s'\n", flag);
}


void print_start_func(const char name[])
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
		print_start_func(__func__);
	#endif

	print_bin_file(file_name);

	#ifdef DEBUG
		print_end_func(__func__);
	#endif

	return 0;
}
