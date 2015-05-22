#include "main.h"

#include "debug.h"
#include "array.h"
#include "proc.h"
#include "cmd.h"
#include "parser.h"
#include "vshell.h"


void SHELL_INIT(int argc, char **argv, Shell *shell)
{
	DEBUG_START("Initializing the shell ...");

	int i;
	for (i = 1; i < argc; i++)
		if (!strcmp(argv[i], "-d"))
			DEBUG = 1;

	shell->processes = create_process_array(10);

	DEBUG_END("done.");
}


void SHELL_RUN(Shell *shell)
{
	DEBUG_START("Running the shell ...");

	Cmd *command;
	int code = CODE_WAIT;
	char line[LINE_LEN];
	bzero(line, LINE_LEN);

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

		delete_command(command);
	}

	delete_command(command);
	DEBUG_END("done.");
}


void SHELL_DUMP(Shell *shell)
{
	DEBUG_START("Dumping the shell into the file ...");

	FILE *dump_stream = fopen(STD_DUMP_FILENAME, "w");
	if (dump_stream == NULL)
	{
		printf("Cannot create the dump file!\n");
		return;
	}

	 DEBUG_SAY("Then i'm trying to close the stream %p ...\n", dump_stream);
	 fclose(dump_stream);

	DEBUG_END("done.");
}


void SHELL_CLOSE(Shell *shell)
{
	if (shell == NULL)
		return;

	DEBUG_START("Closing the shell ...");

	DEBUG_SAY("Deleting the history of commands...\n");
	delete_string_array(shell->history);

	DEBUG_END("done.");
}
