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
	SHELL shell;

	// Init the shell from arguments.
	VSHELL_init(argc, argv, &shell);
	
	// Create a new command "keys", which call keypressor
	// function in the shell.
	VSHELL_add_command(&shell, "ls", "/bin/ls");
	VSHELL_add_command(&shell, "cat", "/bin/cat");
	VSHELL_add_command(&shell, "say", "/bin/echo");
	VSHELL_add_command(&shell, "boss", "/usr/bin/sudo");
	VSHELL_add_command(&shell, "clear", "/usr/bin/clear");
	VSHELL_add_command(&shell, "which", "/usr/bin/which");

	// VSHELL_add_commands_from_dir(&shell, "/bin");

	// Run the shell.
	VSHELL_run(&shell);

	// Dump all data from shell into the file (for debug).
	VSHELL_dump(&shell);

	// Close the shell (remove all created data).
	VSHELL_close(&shell);

	return 0;
}