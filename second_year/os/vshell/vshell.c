#include "main.h"

#include "debug.h"
#include "array.h"
#include "cmd.h"
#include "parser.h"
#include "vshell.h"


void VSHELL_init(int argc, char **argv, SHELL *shell)
{
	int i;
	for (i = 1; i < argc; i++)
		if (!strcmp(argv[i], "-d"))
			DEBUG = 1;

	DEBUG_START("Initializing the shell ...");

	shell->username = "zerlok";
	shell->history = get_string_array(0);

	DEBUG_END("done.");
}


void VSHELL_run(SHELL *shell)
{
	Call *cmd_call;
	int code = CODE_WAIT;
	int indx = 0;
	char c = 0;
	char line[LINE_LEN];
	bzero(line, LINE_LEN);

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
		
		code = do_cmd(cmd_call);

		// TODO: Push into history
		// if (code != CODE_WAIT) {
		// 	push_into_string_array(line, shell->history);
		// }

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

	show_string_array(shell->history, dump_stream);

	// DEBUG_SAY("Then i'm trying to close the stream %p ...\n", dump_stream);
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

	DEBUG_END("done.");
}