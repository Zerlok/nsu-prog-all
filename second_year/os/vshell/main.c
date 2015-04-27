#include "main.h"

#include "debug.h"
#include "array.h"
#include "cmd.h"
#include "parser.h"
#include "vshell.h"


int DEBUG = 0;
int LAYER = 0;


int main(int argc, char **argv, char **envp)
{
	environ = envp;

	SHELL shell;
	// Init the shell from arguments.
	VSHELL_init(argc, argv, &shell);
	// Run the shell.
	VSHELL_run(&shell);
	// Dump all data from shell into the file (for debug).
	// VSHELL_dump(&shell);
	// Close the shell (remove all created data).
	VSHELL_close(&shell);

	return 0;
}