#include "main.h"
#include "streams.h"
#include "signals.h"
#include "array.h"
#include "cmd.h"
#include "proc.h"
#include "parser.h"
#include "vshell.h"
#include "launcher.h"


int DEBUG = 0;
int LAYER = 0;


int main(int argc, char **argv, char **envp)
{
	environ = envp;

	SWITCH_DEBUG(argc, argv);

	Shell shell;
	SHELL_INIT(argc, argv, &shell);
	SHELL_RUN(&shell);
	SHELL_CLOSE(&shell);

	return 0;
}
