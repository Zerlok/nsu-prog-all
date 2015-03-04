#include "main.h"

#include "array.h"
#include "cmd.h"
#include "vshell.h"


// void handle_signal(int signum)
// {
// 	printf("\n%d signal was caught!", signum);
// 	fflush(stdout);
// }


void VSHELL_init(int argc, char **argv, SHELL *shell)
{
	int i;
	for (i = 1; i < argc; i++)
		if (!strcmp(argv[i], "-d"))
			DEBUG = 1;

	if (DEBUG)
		printf("\nInitializing the shell...\n");

	shell->username = "zerlok";
	shell->history = get_array(0);
	shell->cmds = get_commands(10);

	if (DEBUG)
	{
		printf("History array: ");
		show_array(shell->history);

		printf("Cmds array: ");
		show_commands(shell->cmds);
	}
}


void VSHELL_add_command(
		SHELL *shell,
		char *command_name,
		void (*function)(void))
{
	push_into_commands(command_name, function, shell->cmds);
}


void VSHELL_run(SHELL *shell)
{
	StringArray *args = get_array(ARGS_BUFF);
	int code = CODE_WAIT;
	int indx = 0;
	char c = 0;
	char line[LINE_BUFF];
	bzero(line, LINE_BUFF);

	if (DEBUG)
		printf("\nRunning the shell...\n");

	// signal(SIGINT, SIG_IGN);
	// signal(SIGINT, handle_signal);

	while(code != CODE_EXIT)
	{
		printf(">>> ");

		fgets(line, LINE_BUFF, stdin);
		split_line_to_args(line, args);
		code = do_cmd(args, shell->cmds);

		if (code != CODE_WAIT)
			push_into_array(line, shell->history);

		switch (code)
		{
			case CODE_SUCCESS:
			{
				printf("%s: command was run.\n", args->data[0]);
				break;
			}
			case CODE_UNKNOWN_CMD:
			{
				printf("%s: command not found.\n", args->data[0]);
				break;
			}
		}

		clear_array(args);
	}
}


void VSHELL_close(SHELL *shell)
{
	if (DEBUG)
		printf("\nClosing the shell...\n");

	if (DEBUG)
	{
		printf("Deleting the history of commands...\n");
		// show_array(shell->history);
	}
	delete_array(shell->history);

	if (DEBUG)
		printf("Deleting the commands...\n");
	delete_commands(shell->cmds);
}