#include "main.h"

#include "history.h"
#include "cmd.h"
#include "vshell.h"


void VSHELL_init(int argc, char **argv, SHELL *shell)
{
	printf("\nInitializing the shell...\n");

	printf("Creating the history...\n");
	shell->history = get_history(0);

	printf("Creating the array of commands...\n");
	shell->cmds = get_commands(10);
}


int parse_cmd(char *line, Commands *cmds)
{
	if (!strcmp(line, cmds->name[0]))
		return CMD_EXIT;

	size_t i;

	for (i = 1; i < cmds->used_length; i++)
	{
		if (!stdcmp(line, cmds->name[i]))
			*(cmds->func[i])();
	}
}


void VSHELL_run(SHELL *shell)
{
	int cmd = CMD_EXIT;

	printf("\nRunning the shell...\n");

	show_history(shell->history);
	show_commands(shell->cmds);
	
	printf("Welcome to the Vshell (v0.001 alpha).\n");

	// while (cmd == CMD_EXIT)
	// {
	// 	scanf("%s", );
	// }
}