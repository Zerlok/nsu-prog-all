#include "main.h"
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

	TOGGLE_DEBUG(argc, argv);

	Shell shell;

	SHELL_INIT(argc, argv, &shell);
	SHELL_RUN(&shell);
	SHELL_CLOSE(&shell);

	return 0;
}
