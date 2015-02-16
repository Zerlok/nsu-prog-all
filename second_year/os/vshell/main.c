#include "main.h"

#include "array.h"
#include "cmd.h"
#include "vshell.h"


int main(int argc, char **argv)
{
	SHELL shell;

	VSHELL_init(argc, argv, &shell);

	VSHELL_run(&shell);

	VSHELL_close(&shell);

	return 0;
}