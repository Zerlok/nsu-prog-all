#include "main.h"

#include "debug.h"
#include "array.h"
#include "cmd.h"
#include "parser.h"
#include "vshell.h"


// void handle_signal(int signum)
// {
// 	printf("\n%d signal was caught!", signum);
// 	fflush(stdout);
// }


// int VSHELL_CMD_EXIT()
// {
// 	return CODE_EXIT;
// }


// int VSHELL_CMD_HELP(CmdArray *p_cmds)
// {
// 	static CmdArray *cmds = NULL;

// 	if (cmds == NULL)
// 	{
// 		cmds = p_cmds;

// 		return CODE_SUCCESS;
// 	}

// 	printf("Commands : ");
// 	show_commands_array(cmds);
// 	printf("%s\n", );

// 	return CODE_SUCCESS;
// }


void VSHELL_init(int argc, char **argv, SHELL *shell)
{
	int i;
	for (i = 1; i < argc; i++)
		if (!strcmp(argv[i], "-d"))
			DEBUG = 1;

	DEBUG_START("Initializing the shell ...");

	shell->username = "zerlok";
	shell->history = get_string_array(0);
	shell->cmds = get_commands_array(10);

	DEBUG_END("done.");
}


int VSHELL_add_command(
		SHELL *shell,
		char *command_name,
		char *filename)
{
	if ((shell == NULL)
		|| (command_name == NULL)
		|| (filename == NULL))
		return 0;

	DEBUG_START("Creating a new command in the shell ...");

	push_into_commands_array(command_name, filename, shell->cmds);

	DEBUG_END("done.");

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

	// VSHELL_CMD_HELP(shell->cmds);

	// signal(SIGINT, SIG_IGN);
	// signal(SIGINT, handle_signal);

	DEBUG_START("Running the shell ...");

	while(code != CODE_EXIT)
	{
		printf(LINE_START_SYMBOL);

		fgets(line, LINE_LEN, stdin);
		
		cmd_call = get_command_call(line);

		if (cmd_call == NULL)
			continue;
		
		code = do_cmd(cmd_call, shell->cmds);

		// if (code != CODE_WAIT)
		// 	push_into_string_array(line, shell->history);

		switch (code)
		{
			case CODE_FAIL:
			{
				printf("%s: command was crashed.\n", cmd_call->origin);
				break;
			}

			case CODE_INVALID_CALL:
			{
				printf("%s: invalid command call.\n", cmd_call->origin);
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

	delete_command_call(cmd_call);

	DEBUG_END("done.");
}


void VSHELL_dump(SHELL *shell)
{
	DEBUG_START("Dumping the shell into the file ...");

	FILE *dump_stream = fopen(STD_DUMP_FILENAME, "w");

	if (dump_stream == NULL)
	{
		printf("Cannot create the dump file!\n");
		return;
	}

	show_commands_array(shell->cmds, dump_stream);
	show_string_array(shell->history, dump_stream);

	DEBUG_SAY("Then i'm trying to close the stream %p ...\n", dump_stream);

	// fclose(dump_stream);

	DEBUG_END("done.");
}


void VSHELL_close(SHELL *shell)
{
	if (shell == NULL)
		return;

	DEBUG_START("Closing the shell ...");
	// free(shell->username);

	DEBUG_SAY("Deleting the history of commands...\n");
	delete_string_array(shell->history);

	DEBUG_SAY("Deleting the commands...\n");
	delete_commands_array(shell->cmds);

	DEBUG_END("done.");
}