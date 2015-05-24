#include "main.h"
#include "streams.h"
#include "cmd.h"
#include "proc.h"
#include "vshell.h"
#include "launcher.h"


void launch_process(Process *proc, char **argv, int termgrp)
{
	DEBUG_START("Launching the process (%s), pid %d", argv[0], proc->pid);

	if (proc->pgid == 0)
		proc->pgid = proc->pid;

	// Put process into process group.
	setpgid(proc->pid, proc->pgid);

	// Give process group the terminal.
	if (!(proc->is_in_bg))
		tcsetpgrp(termgrp, proc->pgid);

	/* Set the handling for command control signals back to the default.  */
//	signal (SIGINT, SIG_DFL);
//	signal (SIGQUIT, SIG_DFL);
//	signal (SIGTSTP, SIG_DFL);
//	signal (SIGTTIN, SIG_DFL);
//	signal (SIGTTOU, SIG_DFL);
//	signal (SIGCHLD, SIG_DFL);

	// Redirect inputs, if necessary.
	redirect_stream(STDIN_FILENO, proc->in_fileno);
	redirect_stream(STDOUT_FILENO, proc->out_fileno);
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
	int in_fileno = -1;
	int proc_pipes[2];
	Process *current_process;

	// For each pipe.
	Cmd *current_command;
	for (current_command = command;
		 current_command != NULL;
		 current_command = current_command->pipe)
	{
		current_process = create_process(current_command->origin);

		// File input/output/append/error redirect setup.
		DEBUG_SAY("Applying descriptors ...");
		if (current_command->ins == NULL)
			current_process->in_fileno = create_stream(current_command->ins, INPUT_STREAM_FLAGS);

		if (current_command->outs == NULL)
			current_process->out_fileno = create_stream(current_command->outs, OUTPUT_STREAM_FLAGS);

		else if (current_command->appends == NULL)
			current_process->out_fileno = create_stream(current_command->appends, APPEND_STREAM_FLAGS);

		if (current_command->errs == NULL)
			current_process->err_fileno = create_stream(current_command->errs, ERROR_STREAM_FLAGS);

		DEBUG_SAY("Applying pipes ...");
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

		// Forking.
		DEBUG_SAY("Forking ...");
		child_id = fork();

		if (child_id < 0) // Do it if fork failed.
		{
			printf("Cannot create a fork.\n");
			DEBUG_END("failed (fork failed).");
			return CODE_FAIL;
		}
		else if (child_id > 0) // Do it in PARENT process.
		{
			current_process->pid = child_id;
			waitpid(current_process->pid, &status, 0);
		}
		else // Do it in CHILD process.
		{
			current_process->pid = getpid();
			launch_process(current_process, current_command->argv, shell->input_fileno);
		}

		// Clearing pipes.
		if (current_process->in_fileno != STDIN_FILENO)
			close(current_process->in_fileno);
		if (current_process->out_fileno != STDOUT_FILENO)
			close(current_process->out_fileno);

		delete_process(current_process);
	}

	DEBUG_END("done (successfull launch).");
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
