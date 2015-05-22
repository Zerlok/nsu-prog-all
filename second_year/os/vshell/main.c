#include "main.h"

#include "debug.h"
#include "array.h"
#include "proc.h"
#include "cmd.h"
#include "parser.h"
#include "vshell.h"


int DEBUG = 0;
int LAYER = 0;


int main(int argc, char **argv, char **envp)
{
	environ = envp;

	DEBUG_START("GUCKC");

	Shell shell;
	// Init the shell from arguments.
	SHELL_INIT(argc, argv, &shell);
	// Run the shell.
	SHELL_RUN(&shell);
	// Dump all data from shell into the file (for debug).
	// SHELL_dump(&shell);
	// Close the shell (remove all created data).
	SHELL_CLOSE(&shell);

	DEBUG_END("GUGUGUG");

	return 0;
}
