
#define TESTMODE_FLAG "--test"
#define TESTMODE_CODE 9000
#define TESTMODE_ERROR -9000


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
	printf("\n>>>---RUN--->>>\t'%s' function\n", name);
}

void print_end_func(const char name[])
{
	printf("<<<---END---<<<\t'%s' function\n\n", name);
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

// void print_flag(char flag[]);
// void print_start_func(const char name[]);
// void print_end_func(const char name[]);
// void print_here(const char name[], const int line);
// void print_decor();
// void decorate(char str[]);

int run_test(char *file_name);
