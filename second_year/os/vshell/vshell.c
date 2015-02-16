#include "main.h"

#include "array.h"
#include "cmd.h"
#include "vshell.h"


void handle_signal(int signum)
{
	printf("\n[%d] ", signum);
	fflush(stdout);
}


void VSHELL_init(int argc, char **argv, SHELL *shell)
{
	printf("\nInitializing the shell...\n");

	shell->username = "zerlok";
	shell->history = get_array(0);
	shell->cmds = get_commands(10);

	show_array(shell->history);
	show_commands(shell->cmds);
}


void VSHELL_run(SHELL *shell)
{
	StringArray *args = get_array(ARGS_BUFF);
	int code = CODE_WAIT;
	int indx = 0;
	char c = 0;
	char line[LINE_BUFF];
	bzero(line, LINE_BUFF);

	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_signal);

	printf("\nRunning the shell...\n");
	
	// printf(">>> ");
	// while ((c != EOF)
	// 	&& (code != CODE_EXIT))
	while(code != CODE_EXIT)
	{
		// while (c != LINE_END)
		// {
		// 	c = getchar();

		// 	if (c == EOF)
		// 	{
		// 		break;
		// 	}
		// 	else if (c == LINE_SEPARATOR)
		// 	{
		// 		push_into_array(line, args);
		// 		bzero(line, LINE_BUFF);
		// 		indx = 0;
		// 	}
		// 	else 
		// 	{
		// 		line[indx++] = c;
		// 	}
		// }
		printf(">>> ");

		fgets(line, LINE_BUFF, stdin);

		split_line_to_args(line, args);
		
		code = do_cmd(args, shell->cmds);

		switch (code)
		{
			case CODE_UNKNOWN_CMD:
			{
				printf("%s: command not found.\n", args->data[0]);
				break;
			}
			case CODE_SUCCESS:
			{
				printf("%s: done.\n", args->data[0]);
				break;
			}
		}

		clear_array(args);
	}
}


void VSHELL_close(SHELL *shell)
{
	printf("\nClosing the shell...\n");

	printf("Deleting the history...\n");
	delete_array(shell->history);

	printf("Deleting the commands...\n");
	delete_commands(shell->cmds);
}