#include "main.h"

#include "debug.h"
#include "array.h"
#include "cmd.h"


void redirect_stream(int old_stream, char *filename, int flags)
{
	int new_stream = open(filename, flags, 0644);
	DEBUG_SAY("Opened stream: %d\n", new_stream);
	
	if (new_stream == -1)
	{
		perror(strerror(errno));
		return;
	}
	
	dup2(new_stream, old_stream);
	close(new_stream);
}


int do_cmd(Call *call)
{
	if ((call == NULL)
		|| (call->origin == NULL))
		return CODE_WAIT;

	if (!(call->is_valid))
		return CODE_INVALID_CALL;

	DEBUG_START("Calling the %s command ...", call->origin);

	if (!strcmp(call->origin, CMD_EXIT))
	{
		DEBUG_END("done (exit).");
		return CODE_EXIT;
	}

	int status;
	int i;
	pid_t id;
	pid_t pid;
	pid_t gid;
	pid_t sid;

	// Forking
	pid = getpid();
	gid = getpgid(pid);
	DEBUG_SAY("Forking from process %d %d ...\n", pid, gid);
	id = fork();

	if (id < 0) // Do it if fork failed.
	{
		printf("Cannot create a fork.\n");
		DEBUG_END("done (failed fork).");
		return CODE_FAIL;
	}
	else if (id > 0) // Do it in PARENT process.
	{
		// if 
		waitpid(id, &status, 0);
		DEBUG_SAY("Parent id: %d %d %d\n", id, getpid(), getpgid(id));
	}
	else // Do it in CHILD process.
	{
		pid = getpid();
		DEBUG_SAY("Child id: %d %d %d\n", id, getpid(), getpgid(id));

		// Show all calling arguments. 
		DEBUG_SAY("Calling '%s' with arguments: ", call->origin);
		if (DEBUG)
		{
			int arg_index;
			for (arg_index = 0; arg_index < call->argc; arg_index++)
				printf("%s ", call->argv[arg_index]);
			printf("\n");
		}

		// Redirect inputs.
		if (call->ins != NULL)
			redirect_stream(STDIN_FILENO, call->ins, O_RDONLY);

		if (call->outs != NULL)
			redirect_stream(STDOUT_FILENO, call->outs, O_WRONLY | O_CREAT | O_TRUNC);

		else if (call->appends != NULL)
			redirect_stream(STDOUT_FILENO, call->appends, O_WRONLY | O_CREAT | O_APPEND);

		DEBUG_SAY("Is process running in background? %d\n", call->is_in_background);
		
		// if (gid == 0)
		// 	gid = pid;
		
		// setpgid(pid, gid);
		
		// if (!(call->is_in_background))
		// 	tcsetpgrp(shell_terminal, gid);

		// sid = setsid();
		// printf("Process id: %d\n", getpid());
		status = execvpe(call->origin, call->argv, environ);
		
		// If exec failed.
		if (status == -1)
		{
			DEBUG_END("done (failed exec).");
			return CODE_FAIL;
		}
	} // ENDIF (CHILD process)

	DEBUG_END("done (success fork).");
	return CODE_SUCCESS;
}
