#include "main.h"

#include "array.h"
#include "cmd.h"
#include "vshell.h"


void VSHELL_init(int argc, char **argv, SHELL *shell)
{
	printf("\nInitializing the shell...\n");

	shell->username = "zerlok";
	shell->history = get_array(0);
	shell->cmds = get_commands(10);
}


void VSHELL_run(SHELL *shell)
{
	int code = CODE_WAIT;
	char line[LINE_BUFF];

	printf("\nRunning the shell...\n");

	show_array(shell->history);
	show_commands(shell->cmds);
	
	printf("Welcome to the Vshell (v0.001 alpha).\n");

	while(code != CODE_EXIT)
	{
		printf(">>> ");
		
		fgets(line, sizeof(line), stdin);
		
		code = parse_cmd(line, shell->cmds);

		if (code == CODE_UNKNOWN_CMD)
		{
			printf("### unknown cmd.\n");
		}
		else
		{
			printf("\t working...\n");
		}
	}
}


void VSHELL_close(SHELL *shell)
{
	printf("\nClosing the shell...\n");

	printf("Deleting the history...\n");
	free(shell->history);

	printf("Deleting the commands...\n");
	free(shell->cmds);
}