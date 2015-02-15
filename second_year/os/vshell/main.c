#include "main.h"

#include "history.h"
#include "cmd.h"
#include "vshell.h"


int main(int argc, char **argv)
{
	SHELL shell;

	VSHELL_init(argc, argv, &shell);

	VSHELL_run(&shell);

	return 0;
}