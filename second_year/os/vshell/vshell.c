#include "main.h"

#include "array.h"
#include "cmd.h"
#include "parser.h"
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
		printf("\nInitializing the shell ... ");

	shell->username = "zerlok";
	shell->history = get_string_array(0);
	shell->cmds = get_commands_array(10);

	if (DEBUG)
		printf("done.\n");
}


int VSHELL_add_command(
		SHELL *shell,
		char *command_name,
		int (*function)(FILE*, FILE*, StringArray*))
{
	if ((shell == NULL)
		|| (command_name == NULL)
		|| (function == NULL))
		return 0;

	if (DEBUG)
		printf("\nCreating a new command in the shell ... ");

	push_into_commands_array(command_name, function, shell->cmds);

	if (DEBUG)
		printf("done.\n");

	return 1;
}


void VSHELL_run(SHELL *shell)
{
	CmdArguments *cmd_call;
	int code = CODE_WAIT;
	int indx = 0;
	char c = 0;
	char line[LINE_LEN];
	bzero(line, LINE_LEN);

	if (DEBUG)
	{
		printf("\nRunning the shell ... \n");

		printf("Cmds array: ");
		show_commands_array(shell->cmds, stdout);
	
		printf("History array: ");
		show_string_array(shell->history, stdout);
	}

	// signal(SIGINT, SIG_IGN);
	// signal(SIGINT, handle_signal);

	while(code != CODE_EXIT)
	{
		printf(LINE_START_SYMBOL);

		fgets(line, LINE_LEN, stdin);
		printf("Input line: %s\n", line);
		
		cmd_call = get_command_call(line);

		if (cmd_call->is_valid)
			code = do_cmd(cmd_call, shell->cmds);

		// if (code != CODE_WAIT)
		// 	push_into_string_array(line, shell->history);

		switch (code)
		{
			case CODE_SUCCESS:
			{
				printf("%s: command was successfully run.\n", cmd_call->origin);
				break;
			}

			case CODE_FAIL:
			{
				printf("%s: command was crashed.\n", cmd_call->origin);
				break;
			}

			case CODE_UNKNOWN_CMD:
			{
				printf("%s: command not found.\n", cmd_call->origin);
				break;
			}
		}

		clear_command_call(cmd_call);
	}

	if (DEBUG)
		printf("\nDone.\n");
}


void VSHELL_dump(SHELL *shell)
{
	FILE *dump_stream = fopen(STD_DUMP_FILENAME, "w");

	if (dump_stream == NULL)
	{
		printf("Cannot create the dump file!\n");
		return;
	}

	show_commands_array(shell->cmds, dump_stream);
	show_string_array(shell->history, dump_stream);

	fclose(dump_stream);
}


void VSHELL_close(SHELL *shell)
{
	if (DEBUG)
		printf("\nClosing the shell ...\n");

	if (DEBUG)
		printf("Deleting the history of commands...\n");
	delete_string_array(shell->history);

	if (DEBUG)
		printf("Deleting the commands...\n");
	delete_commands_array(shell->cmds);

	if (DEBUG)
		printf("\nDone.\n");
}