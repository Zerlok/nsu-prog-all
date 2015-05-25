#include "main.h"
#include "signals.h"
#include "array.h"
#include "cmd.h"
#include "proc.h"
#include "vshell.h"
#include "launcher.h"


void SHELL_INIT(int argc, char **argv, Shell *shell)
{
	DEBUG_START("Initializing the shell ...");

	shell->input_fileno = STDIN_FILENO;
	shell->is_interactive = isatty(shell->input_fileno);

	if (shell->is_interactive)
	{
		DEBUG_SAY("Current shell is interactive.\n");
		shell->processes = create_process_list();
	}
	else
		DEBUG_SAY("Current shell is not interactive\n");

	/* Loop until we are in the foreground.  */
	while (tcgetpgrp(shell->input_fileno) != (shell->pgid = getpgrp()))
		kill(-shell->pgid, SIGTTIN);

	/* Ignore interactive and job-control signals.  */
	ignore_signals();

	/* Put ourselves in our own process group.  */
	shell->pgid = getpid();
	if (setpgid(shell->pgid, shell->pgid) < 0)
	{
		perror("Couldn't put the shell in its own process group");
		exit(1);
	}

	/* Grab control of the terminal.  */
	tcsetpgrp(shell->input_fileno, shell->pgid);

	/* Save default terminal attributes for shell.  */
	tcgetattr(shell->input_fileno, shell->term_modes);

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

	delete_process_list(shell->processes);

	DEBUG_END("done.");
}


void put_process_in_foreground(ProcessGroup *group, int cont, Shell *shell)
{
	DEBUG_START("Making process as foreground ...");

	/* Put the job into the foreground.  */
	tcsetpgrp (shell->input_fileno, group->pgid);

	/* Send the job a continue signal, if necessary.  */
	if (cont)
	{
		tcsetattr(shell->input_fileno, TCSADRAIN, group->term_modes);
		if (kill(-group->pgid, SIGCONT) < 0)
			perror("kill (SIGCONT)");
	}

	/* Wait for it to report.  */
	wait_for_process_group(group, shell->processes);

	/* Put the shell back in the foreground.  */
	tcsetpgrp(shell->input_fileno, shell->pgid);

	/* Restore the shell’s terminal modes.  */
	tcgetattr(shell->input_fileno, group->term_modes);
	tcsetattr(shell->input_fileno, TCSADRAIN, shell->term_modes);

	DEBUG_END("done.");
}


void put_process_in_background(ProcessGroup *group, int cont)
{
	DEBUG_START("Making process as background ...");

	/* Send the job a continue signal, if necessary.  */
	if (cont)
		if (kill (-group->pgid, SIGCONT) < 0)
			perror(strerror(errno));

	DEBUG_END("done.");
}


int set_process_status(pid_t pid, int status, ProcessList *processes)
{
	DEBUG_START("Setting up process status with pid %d", pid);

	Process *proc;
	if ((pid > 0)
			&& (processes != NULL))
	{
		/* Update the record for the process.  */
		proc = find_process_in_list(pid, processes);
		if (proc != NULL)
		{
			DEBUG_SAY("Found process: ");
			if (DEBUG)
				show_process(proc);

			proc->status = status;

			if (WIFSTOPPED(status))
			{
				proc->is_stopped = 1;
			}
			else
			{
				proc->is_completed = 1;

				if (WIFSIGNALED(status))
					fprintf(stderr, "%d: Terminated by signal %d.\n", pid, WTERMSIG (proc->status));
			}

			DEBUG_END("done (returning 0)");
			return 0;
		}

		fprintf(stderr, "No child process %d.\n", pid);
	}

	DEBUG_END("failed.");
	return -1;
}


void update_processes(ProcessList *processes)
{
	DEBUG_START("Updating the status ...");

	int status;
	pid_t pid;

	do
		pid = waitpid(WAIT_ANY, &status, WUNTRACED|WNOHANG);
	while (!set_process_status(pid, status, processes));

	DEBUG_END("done.");
}


void wait_for_process_group(ProcessGroup *group, ProcessList *processes)
{
	DEBUG_START("Waiting for process group with pgid %d ...", group->pgid);

	int status;
	pid_t pid;

	do
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (!set_process_status(pid, status, processes)
			&& (!was_process_group_stopped(group))
			&& (!was_process_group_completed(group)));

	DEBUG_END("done.");
}


void update_processes_status(ProcessList *processes)
{
	/* Update status information for child processes.  */
	DEBUG_START("Notifying processes ...");
	update_processes(processes);

	ProcessGroup *cursor = processes->first;
	ProcessGroup *group;
	while (cursor != NULL)
	{
		/* If all processes have completed, tell the user the job has
		completed and delete it from the processes of active jobs.  */
		if (was_process_group_stopped(cursor))
		{
			printf("%s completed.", (cursor->head)->name);
			group = cursor->next_group;
			remove_process_group_from_list(cursor->pgid, processes);
			cursor = group;
			continue;
		}

		/* Notify the user about stopped jobs,
		marking them so that we won’t do this more than once.  */
		else if (was_process_group_stopped(cursor))
			printf("%s stopped.", (cursor->head)->name);

		cursor = cursor->next_group;
	}
}
