#include "main.h"
#include "streams.h"
#include "signals.h"
#include "cmd.h"
#include "proc.h"
#include "vshell.h"
#include "launcher.h"


void launch_process(Process *proc, char **argv, Shell *shell)
{
	DEBUG_START("Launching the process (%s), pid %d", argv[0], proc->pid);

	if (shell->is_interactive)
	{
		if (proc->pgid == 0)
			proc->pgid = proc->pid;

		// Put process into process group.
		setpgid(proc->pid, proc->pgid);

		// Give process group the terminal.
		if (!(proc->is_in_bg))
			tcsetpgrp(shell->input_fileno, proc->pgid);

		/* Set the handling for command control signals back to the default.  */
		handle_signals();
	}

	// Redirect inputs, if necessary.
//	if (proc->in_fileno != STDIN_FILENO)
//		redirect_stream(STDIN_FILENO, proc->in_fileno);
//	if (proc->out_fileno != STDOUT_FILENO)
//		redirect_stream(STDOUT_FILENO, proc->out_fileno);
//	if (proc->err_fileno != STDERR_FILENO)
//		redirect_stream(STDERR_FILENO, proc->err_fileno);

	DEBUG_END("done (executing the child process).");

	execvpe(argv[0], argv, environ);
	perror(argv[0]);
	exit(CODE_FAIL);
}


int launch_command(Cmd *command, Shell *shell)
{
	if ((command == NULL)
			|| (command->origin == NULL))
		return CODE_WAIT;

	if (!(command->is_valid))
		return CODE_INVALID_CMD;

	if (is_builtin_command(command))
		return launch_builtin_command(command, shell);

	DEBUG_START("Launching the '%s' command ...", command->origin);

	pid_t child_id;
	int status;
	int in_fileno = STDIN_FILENO;
	int out_fileno = STDOUT_FILENO;
	int proc_pipes[2];
	Process *current_process;
	ProcessGroup *current_group = create_process_group(0);
	push_process_group_into_list(current_group, shell->processes);

	// For each pipe.
	Cmd *current_command;
	for (current_command = command;
		 current_command != NULL;
		 current_command = current_command->pipe)
	{
		current_process = create_process(current_command->origin);

		// File input/output/append/error redirect setup.
		DEBUG_SAY("Applying descriptors ...\n");
		if (current_command->ins != NULL)
			current_process->in_fileno = create_stream(current_command->ins, INPUT_STREAM_FLAGS);

		if (current_command->outs != NULL)
			current_process->out_fileno = create_stream(current_command->outs, OUTPUT_STREAM_FLAGS);

		else if (current_command->appends != NULL)
			current_process->out_fileno = create_stream(current_command->appends, APPEND_STREAM_FLAGS);

		if (current_command->errs != NULL)
			current_process->err_fileno = create_stream(current_command->errs, ERROR_STREAM_FLAGS);

		DEBUG_SAY("Applying pipes ...\n");
		// Pipes input setup.
		if (in_fileno > 0)
			current_process->in_fileno = in_fileno;

		// Pipe output setup.
		if (current_command->pipe != NULL)
		{
			if (pipe(proc_pipes) < 0)
			{
				perror(strerror(errno));
				exit(CODE_FAIL);
			}

			in_fileno = proc_pipes[0]; // save pipe to the next process.
			current_process->out_fileno = proc_pipes[1];
		}
		else
			current_process->out_fileno = out_fileno;

		// Forking.
		DEBUG_SAY("Forking ...\n");
		child_id = fork();

		// Do it if fork failed.
		if (child_id < 0)
		{
			printf("Cannot create a fork.\n");
			DEBUG_END("failed (fork failed).");
			return CODE_FAIL;
		}

		// Do it in PARENT process.
		else if (child_id > 0)
		{
			current_process->pid = child_id;
			if (shell->is_interactive)
			{
				if (current_group->pgid == 0)
					current_group->pgid = child_id;

				setpgid(child_id, current_group->pgid);
			}

			push_process_in_group(current_process, current_group);

			waitpid(current_process->pid, &status, 0);
		}

		// Do it in CHILD process.
		else
		{
			current_process->pid = getpid();
			launch_process(current_process, current_command->argv, shell);
		}

		// Clearing pipes.
		if (current_process->in_fileno != STDIN_FILENO)
			close(current_process->in_fileno);
		if (current_process->out_fileno != STDOUT_FILENO)
			close(current_process->out_fileno);
	}

	DEBUG_SAY("Command launched.\n");

	if (!(shell->is_interactive))
		wait_for_process_group(current_group, shell->processes);
	else if (command->is_in_background)
		put_process_in_background(current_group, 0);
	else
		put_process_in_foreground(current_group, 0, shell);

	DEBUG_END("done.");
	return CODE_SUCCESS;
}


int is_builtin_command(Cmd *command)
{
	if ((!strcmp(command->origin, "exit"))
			|| (!strcmp(command->origin, "help"))
			|| (!strcmp(command->origin, "jobs"))
			|| (!strcmp(command->origin, "fg")))
		return 1;

	return 0;
}


int launch_builtin_command(Cmd *command, Shell *shell)
{
	if (!strcmp(command->origin, "exit"))
		return CODE_EXIT;

	DEBUG_START("Launching the builtin command ...");

	DEBUG_END("done.");
	return CODE_SUCCESS;
}
