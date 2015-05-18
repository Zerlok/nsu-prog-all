#include "main.h"

#include "debug.h"
#include "array.h"
#include "proc.h"
#include "cmd.h"
#include "parser.h"
#include "vshell.h"


void VSHELL_INIT(int argc, char **argv, SHELL *shell)
{
	int i;
	for (i = 1; i < argc; i++)
		if (!strcmp(argv[i], "-d"))
			DEBUG = 1;

	DEBUG_START("Initializing the shell ...");

	shell->processes = get_process_array(10);
	shell->history = get_string_array(0);

	DEBUG_END("done.");
}


void VSHELL_RUN(SHELL *shell)
{
	Cmd *command;
	int code = CODE_WAIT;
	char line[LINE_LEN];
	bzero(line, LINE_LEN);

	// signal(SIGINT, SIG_IGN);
	// signal(SIGINT, handle_signal);

	DEBUG_START("Running the shell ...");

	while(code != CODE_EXIT)
	{
		printf(LINE_START_SYMBOL);
		fgets(line, LINE_LEN, stdin);
		
		command = build_command(line);

		if (command == NULL)
			continue;
		
        code = run_command(command, shell->processes);

		// TODO: Push into history
		// if (code != CODE_WAIT) {
		// 	push_into_string_array(line, shell->history);
		// }

		clear_command(command);
	}

	delete_command(command);
	DEBUG_END("done.");
}


void VSHELL_DUMP(SHELL *shell)
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


void VSHELL_CLOSE(SHELL *shell)
{
	if (shell == NULL)
		return;

	DEBUG_START("Closing the shell ...");
	// free(shell->username);

	DEBUG_SAY("Deleting the history of commands...\n");
	delete_string_array(shell->history);

	DEBUG_END("done.");
}
