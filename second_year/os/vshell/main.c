#include "main.h"

#include "debug.h"
#include "array.h"
#include "cmd.h"
#include "parser.h"
#include "vshell.h"


int DEBUG = 1;
int LAYER = 0;


int hello_world(FILE *strin, FILE *strout, StringArray *args)
{
	fprintf(strout, "Hello, world!\n");

	return CODE_SUCCESS;
}


int argument_splitter(FILE *strin, FILE *strout, StringArray *args)
{
	fprintf(strout, "Args: ");
	show_string_array(args, strout);

	return CODE_SUCCESS;
}


int keypressor(FILE *strin, FILE *strout, StringArray *args)
{
	printf("Welcome to keypressor!\nType something on keyboard and you will see the keys that you pressed.\nTo exit the program press ESC.\n");

	int ch = 0;

	// Make terminal send all keystrokes directly to stdin.
	system("/bin/stty raw");

	while (ch != 27)
	{		
		ch = getc(strin);

		switch (ch)
		{
			case 13: fprintf(strout, "\b\b\n"); break;
			default: fprintf(strout, "\b"); break;
		}
	}

	// Set normal terminal behavior.
	system("/bin/stty cooked");

	return CODE_SUCCESS;
}


int main(int argc, char **argv, char **envp)
{
	SHELL shell;

	// LAYER = 0;

	// Init the shell from arguments.
	VSHELL_init(argc, argv, &shell);
	
	// Create a new command "keys", which call keypressor
	// function in the shell.
	VSHELL_add_command(&shell, "hello", hello_world);
	VSHELL_add_command(&shell, "splitter", argument_splitter);
	VSHELL_add_command(&shell, "keys", keypressor);

	// Run the shell.
	VSHELL_run(&shell);

	// Dump all data from shell into the file (for debug).
	VSHELL_dump(&shell);

	// Close the shell (remove all created data).
	VSHELL_close(&shell);

	return 0;
}