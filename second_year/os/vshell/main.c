#include "main.h"

#include "array.h"
#include "cmd.h"
#include "vshell.h"


void keypressor()
{
	printf("Welcome to keypressor!\nType something on keyboard and you will see the keys that you pressed.\nTo exit the program press ESC.\n");

	int ch = 0;

	// Make terminal send all keystrokes directly to stdin.
	system("/bin/stty raw");

	while (ch != 27)
	{		
		ch = getc(stdin);

		switch (ch)
		{
			case 13: printf("\b\b\n"); break;
			default: printf("\b"); break;
		}
	}

	// Set normal terminal behavior.
	system("/bin/stty cooked");
}


int main(int argc, char **argv, char **envp)
{
	SHELL shell;

	VSHELL_init(argc, argv, &shell);
	VSHELL_add_command(&shell, "keys", keypressor);

	VSHELL_run(&shell);

	VSHELL_close(&shell);

	return 0;
}