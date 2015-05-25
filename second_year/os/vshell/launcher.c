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

//	 Redirect inputs, if necessary.
	if (proc->in_fileno != STDIN_FILENO)
		redirect_stream(STDIN_FILENO, proc->in_fileno);
	if (proc->out_fileno != STDOUT_FILENO)
		redirect_stream(STDOUT_FILENO, proc->out_fileno);
	if (proc->err_fileno != STDERR_FILENO)
		redirect_stream(STDERR_FILENO, proc->err_fileno);

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
	int proc_pipes[2];
	Process *proc;
	ProcessGroup *group = create_process_group(0);
	push_process_group_into_list(group, shell->processes);

	// For each pipe.
	Cmd *cmd;
	for (cmd = command;
		 cmd != NULL;
		 cmd = cmd->pipe)
	{
		proc = create_process(cmd->origin);

		DEBUG_SAY("Applying descriptors ...\n");
		if (cmd->ins != NULL)
			proc->in_fileno = create_stream(cmd->ins, INPUT_STREAM_FLAGS);

		if (cmd->outs != NULL)
			proc->out_fileno = create_stream(cmd->outs, OUTPUT_STREAM_FLAGS);

		else if (cmd->appends != NULL)
			proc->out_fileno = create_stream(cmd->appends, APPEND_STREAM_FLAGS);

		DEBUG_SAY("Applying pipes ...\n");
		if (in_fileno != STDIN_FILENO)
			proc->in_fileno = in_fileno;

		if (cmd->pipe != NULL)
		{
			if (pipe(proc_pipes) < 0)
			{
				perror(strerror(errno));
				exit(CODE_FAIL);
			}

			in_fileno = proc_pipes[0]; // save pipe to the next process.
			proc->out_fileno = proc_pipes[1];
		}
		else
			proc->out_fileno = STDOUT_FILENO;

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
			close(proc_pipes[0]);
			close(proc_pipes[1]);
			proc->pid = child_id;
			if (shell->is_interactive)
			{
				if (group->pgid == 0)
					proc->pgid = child_id;

				push_process_in_group(proc, group);
				setpgid(child_id, group->pgid);
			}


			waitpid(proc->pid, &status, 0);
		}

		// Do it in CHILD process.
		else
		{
			close(in_fileno);
			close(proc_pipes[1]);
			proc->pid = getpid();
			launch_process(proc, cmd->argv, shell);
		}

		// Clearing pipes.
//		if (proc->in_fileno != STDIN_FILENO)
//			close(proc->in_fileno);
//		if (proc->out_fileno != STDOUT_FILENO)
//			close(proc->out_fileno);
	}

	DEBUG_SAY("Command launched.\n");

	if (!(shell->is_interactive))
		wait_for_process_group(group, shell->processes);
	else if (command->is_in_background)
		put_process_in_background(group, 0);
	else
		put_process_in_foreground(group, 0, shell);

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

	else if (!strcmp(command->origin, "jobs"))
		show_process_list(shell->processes);

	DEBUG_START("Launching the builtin command ...");

	DEBUG_END("done.");
	return CODE_SUCCESS;
}
