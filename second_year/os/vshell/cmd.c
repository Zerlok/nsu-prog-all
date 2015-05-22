#include "main.h"

#include "debug.h"
#include "array.h"
#include "proc.h"
#include "cmd.h"
#include "parser.h"


int redirect_stream(int old_stream, char *filename, int flags)
{
	int new_stream = open(filename, flags, 0644);
	DEBUG_SAY("Opened stream: %d\n", new_stream);
	
	if (new_stream == -1)
	{
		perror(strerror(errno));
		return -1;
	}
	
	dup2(new_stream, old_stream);
	close(new_stream);

	return old_stream;
}


void run_child(pid_t parentid, Cmd *command)
{
	pid_t pid = getpid();
	pid_t gid = parentid;

	DEBUG_START("Running child with pid: %d", pid);

	// Show all commanding arguments.
	DEBUG_SAY("Calling '%s' with arguments: ", command->origin);
	if (DEBUG)
	{
		int arg_index;
		for (arg_index = 0; arg_index < command->argc; arg_index++)
			printf("%s ", command->argv[arg_index]);
		printf("\n");
	}

	// Redirect inputs.
	if (command->ins != NULL)
		redirect_stream(STDIN_FILENO, command->ins, O_RDONLY);

	if (command->outs != NULL)
		redirect_stream(STDOUT_FILENO, command->outs, O_WRONLY | O_CREAT | O_TRUNC);

	else if (command->appends != NULL)
		redirect_stream(STDOUT_FILENO, command->appends, O_WRONLY | O_CREAT | O_APPEND);

	// DEBUG_SAY("Is process running in background? %d\n", command->is_in_background);
	setpgid(pid, gid);
	tcsetpgrp(parentid, pid);

	if (command->is_in_background)
	{
		DEBUG_SAY("Closing the input ...\n");
		// redirect_stream(STDIN_FILENO, "/dev/tty", O_RDONLY);
		// close(STDIN_FILENO);
	}

	DEBUG_END("done (executing child).");
	execvpe(command->origin, command->argv, environ);

	DEBUG_SAY("Exec error: ");
	perror(command->origin);
	exit(CODE_FAIL);
}


int run_command(Cmd *command, ProcessArray *processes)
{
	if ((command == NULL)
			|| (command->origin == NULL))
		return CODE_WAIT;

	if (!(command->is_valid))
	{
		printf("Invalid command.\n");
		return CODE_INVALID_CALL;
	}

	DEBUG_START("Calling the %s command ...", command->origin);

	if (!strcmp(command->origin, CMD_EXIT))
	{
		DEBUG_END("done (exit).");
		return CODE_EXIT;
	}

	int status;
	pid_t gid;
	pid_t id;
	pid_t termid = getpid();

	// Forking
	gid = getpid(); // Group id is a shell pid.
	DEBUG_SAY("Forking from process %d %d ...\n", gid, termid);
	id = fork();

	if (id < 0) // Do it if fork failed.
	{
		printf("Cannot create a fork.\n");
		DEBUG_END("done (failed fork).");
		return CODE_FAIL;
	}
	else if (id > 0) // Do it in PARENT process.
	{
		waitpid(id, &status, 0);
		DEBUG_SAY("Parent pid: %d\n", termid);
	}
	else // Do it in CHILD process.
		run_child(gid, command);

	DEBUG_END("done (successed fork).");
	return CODE_SUCCESS;
}


Cmd *create_empty_command(char *cmd_name)
{
	if (cmd_name == NULL)
		return NULL;

	DEBUG_START("Creating the empty Cmd ...");
	
	Cmd *command = (Cmd*)malloc(sizeof(Cmd));
	command->origin = (char*)calloc(sizeof(char), strlen(cmd_name) + 1);
	command->ins = NULL;
	command->outs = NULL;
	command->appends = NULL;
	command->is_in_background = 0;
	command->argv = NULL;

	strcpy(command->origin, cmd_name);
	
	DEBUG_END("done.");
	return command;
}


Cmd *build_command(char *line)
{
	if ((line == NULL)
			|| (line == 0)
			|| ((*line) == LINE_END_SYMBOL))
		return NULL;

	DEBUG_START("Building a new command from line ...");

	// Initializing the variables...
	size_t i = 1;
	int is_valid = 1; // (true)

	// Splitting the line by spaces.
	StringArray *splitted_line = split(line);
	DEBUG_SAY("After splitting\n");

	if ((splitted_line == NULL)
			|| (splitted_line->used_length == 0))
	{
		DEBUG_END("done.");
		return NULL;
	}
	DEBUG_SAY("After if-else condition\n");

	// Setting up the Cmd structure.
	Cmd *main_command = create_empty_command(splitted_line->data[0]);
	Cmd *command = main_command;
	DEBUG_SAY("After empty command creation\n");

	DEBUG_SAY("%p %p %ld -- %s\n",
			(splitted_line),
			(splitted_line->data),
			(splitted_line->used_length),
			(splitted_line->data)[(splitted_line->used_length)-1]
	);

	StringArray *command_args = get_string_array(1);
	while ((i < splitted_line->used_length)
		   && is_valid)
	{
		// The input stream was set.
		if (!strcmp(splitted_line->data[i], LINE_INPUT_STREAM_STRING))
		{
			DEBUG_SAY("Special symbol '%s' was found\n", splitted_line->data[i]);
			if (i + 1 == splitted_line->used_length)
			{
				is_valid = 0;
				break;
			}

			command->ins = pop_string_from_array(i + 1, splitted_line); // pop argument
		}

		// The output stream was set.
		else if (!strcmp(splitted_line->data[i], LINE_OUTPUT_STREAM_STRING))
		{
			DEBUG_SAY("Special symbol '%s' was found\n", splitted_line->data[i]);
			if (i + 1 == splitted_line->used_length)
			{
				is_valid = 0;
				break;
			}

			command->outs = pop_string_from_array(i + 1, splitted_line); // pop argument
		}

		// The append stream was set.
		else if (!strcmp(splitted_line->data[i], LINE_APPEND_STREAM_STRING))
		{
			DEBUG_SAY("Special symbol '%s' was found\n", splitted_line->data[i]);
			if (i + 1 == splitted_line->used_length)
			{
				is_valid = 0;
				break;
			}

			command->appends = pop_string_from_array(i + 1, splitted_line); // delete argument
		}

		// The background running was set.
		else if (!strcmp(splitted_line->data[i], LINE_BACKGROUND_STRING))
		{
			DEBUG_SAY("Special symbol %s was found\n", splitted_line->data[i]);
			command->is_in_background = 1;
		}

		// Pipe symbol was captured.
		else if (!strcmp(splitted_line->data[i], LINE_PIPE_STRING))
		{
			DEBUG_SAY("Special symbol %s was found\n", splitted_line->data[i]);
			if (i + 1 == splitted_line->used_length)
			{
				is_valid = 0;
				break;
			}

			command->pipe = create_empty_command(splitted_line->data[i + 1]); // delete argument
			command->argc = command_args->used_length;
			command->argv = get_string_array_data(command_args);
			clear_string_array(command_args);

			DEBUG_SHOW_CMD(command);

			command = command->pipe;
		}

		// The argument was found
		else
			push_into_string_array(
					splitted_line->data[i],
					command_args
			);

		++i;
	} // ENDWHILE (splitted_line->used_length)

	command->argc = command_args->used_length;
	command->argv = get_string_array_data(command_args);

	DEBUG_SHOW_CMD(main_command);

	delete_string_array(command_args);
	delete_string_array(splitted_line);
	
	DEBUG_END("done.");
	return main_command;
}


void clear_command(Cmd *command)
{
	if (command == NULL)
		return;

	DEBUG_START("Clearing the command call ...");

	DEBUG_SAY("Removing argv ...\n");
	int i;
	for (i = 0; i < command->argc; i++)
		free(command->argv[i]);
	free(command->argv);

	command->argc = 0;
	
	DEBUG_SAY("Removing origin ...\n");
	free(command->origin);
	DEBUG_SAY("Removing ins ...\n");
	free(command->ins);
	DEBUG_SAY("Removing outs ...\n");
	free(command->outs);
	DEBUG_SAY("Removing appends ...\n");
	free(command->appends);

	DEBUG_END("done.");
}


void delete_command(Cmd *command)
{
	if (command == NULL)
		return;

	DEBUG_START("Deleting the command call ...");

	clear_command(command);
	free(command);

	DEBUG_END("done.");
}
