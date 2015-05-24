#include "main.h"
#include "array.h"
#include "proc.h"
#include "cmd.h"
#include "parser.h"
#include "vshell.h"


void SHELL_INIT(int argc, char **argv, Shell *shell)
{
	DEBUG_START("Initializing the shell ...");

	shell->input_fileno = STDIN_FILENO;
	shell->is_interactive = isatty(shell->input_fileno);

	if (shell->is_interactive)
	{
		DEBUG_SAY("Current shell is interactive.\n");
		shell->processes = create_process_array(10);
	}
	else
		DEBUG_SAY("Current shell is not interactive\n");

	/* Loop until we are in the foreground.  */
//	while (tcgetpgrp (shell_terminal) != (shell_pgid = getpgrp ()))
//	  kill (- shell_pgid, SIGTTIN);

	/* Ignore interactive and job-control signals.  */
//	signal(SIGINT, SIG_IGN);
//	signal(SIGQUIT, SIG_IGN);
//	signal(SIGTSTP, SIG_IGN);
//	signal(SIGTTIN, SIG_IGN);
//	signal(SIGTTOU, SIG_IGN);
//	signal(SIGCHLD, SIG_IGN);

	/* Put ourselves in our own process group.  */
	shell->pgid = getpid();
	if (setpgid(shell->pgid, shell->pgid) < 0)
	{
		perror("Couldn't put the shell in its own process group");
		exit(1);
	}

	/* Grab control of the terminal.  */
	tcsetpgrp(shell->input_fileno, shell->pgid);

	DEBUG_END("done.");
}


void SHELL_RUN(Shell *shell)
{
	if (!(shell->is_interactive))
		return;

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
		
		code = launch_command(command, shell);
		delete_command(command);
	}

	DEBUG_END("done.");
}


void SHELL_CLOSE(Shell *shell)
{
	if (shell == NULL)
		return;

	DEBUG_START("Closing the shell ...");

	delete_process_array(shell->processes);

	DEBUG_END("done.");
}
