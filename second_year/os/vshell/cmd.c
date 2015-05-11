#include "main.h"

#include "debug.h"
#include "array.h"
#include "parser.h"
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


int run_command(Cmd *command)
{
	if ((command == NULL)
		|| (command->origin == NULL))
		return CODE_WAIT;

	if (!(command->is_valid))
		return CODE_INVALID_CALL;

	DEBUG_START("Calling the %s command ...", command->origin);

	if (!strcmp(command->origin, CMD_EXIT))
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
	gid = getpid(); // Group id is a shell pid.
	DEBUG_SAY("Forking from process %d ...\n", gid);
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
		DEBUG_SAY("Parent pid: %d\n", getpid());
	}
	else // Do it in CHILD process.
	{
		pid = getpid();
		DEBUG_SAY("Child pid: %d\n", pid);

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
		tcsetpgrp(gid, gid);
		
		if (command->is_in_background)
		{
			DEBUG_SAY("Closing the input ...\n");
			redirect_stream(STDIN_FILENO, "/dev/tty", O_RDONLY);
			// close(STDIN_FILENO);
		}

		printf("pid: %d, gid: %d\n", pid, gid);
		status = execvpe(command->origin, command->argv, environ);
		
		// If exec failed.
		if (status == -1)
		{
			perror(command->origin);
			DEBUG_END("done (failed exec).");
			exit(CODE_FAIL);
		}
	} // ENDIF (CHILD process)

	DEBUG_END("done (successed fork).");
	return CODE_SUCCESS;
}


Cmd *get_empty_command(char *cmd_name)
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


Cmd *get_command(char *line)
{
	if ((line == NULL)
		|| (line == 0)
		|| ((*line) == LINE_END_SYMBOL))
		return NULL;

	DEBUG_START("Creating a new command call ...");

	// Initializing the variables...
	size_t i = 0;
	int is_valid = 1; // (true)

	// Splitting the line by spaces.
	StringArray *args_array = split(line);
	DEBUG_SAY("After splitting\n");

	if ((args_array == NULL)
		|| (args_array->used_length == 0))
	{
		DEBUG_END("done.");
		return NULL;
	}

	DEBUG_SAY("After if-else condition\n");

	// Setting up the Cmd structure.
	Cmd *command = get_empty_command(args_array->data[0]);

	DEBUG_SAY("After empty command call creation\n");
	DEBUG_SAY("%p %p %ld -> %s\n", args_array, args_array->data, args_array->used_length, args_array->data[args_array->used_length-1]);

	while ((i < args_array->used_length)
		&& (is_valid))
	{
		// The input stream was set.
		if (!strcmp(args_array->data[i], LINE_INPUT_STREAM_STRING))
		{
			if (i + 1 == args_array->used_length)
			{
				is_valid = 0;
				break;
			}

			command->ins = (char*)calloc(sizeof(char), strlen(args_array->data[i + 1]) + 1);
			strcpy(command->ins, args_array->data[i + 1]);

			DEBUG_SAY("Pop '%s' in args_array (%ld < %ld)\n", args_array->data[i], i, args_array->used_length);
			delete_string_from_array(i, args_array); // delete LINE_INPUT_STREAM_STRING
			delete_string_from_array(i, args_array); // delete argument
		}

		// The output stream was set.
		else if (!strcmp(args_array->data[i], LINE_OUTPUT_STREAM_STRING))
		{
			if (i + 1 >= args_array->used_length)
			{
				is_valid = 0;
				break;
			}

			command->outs = (char*)calloc(sizeof(char), strlen(args_array->data[i + 1]) + 1);
			strcpy(command->outs, args_array->data[i + 1]);

			DEBUG_SAY("Pop '%s' in args_array (%ld < %ld)\n", args_array->data[i], i, args_array->used_length);
			delete_string_from_array(i, args_array); // delete LINE_OUTPUT_STREAM_STRING
			delete_string_from_array(i, args_array); // delete argument
		}

		// The append stream was set.
		else if (!strcmp(args_array->data[i], LINE_APPEND_STREAM_STRING))
		{
			if (i + 1 == args_array->used_length)
			{
				is_valid = 0;
				break;
			}
			
			command->appends = (char*)calloc(sizeof(char), strlen(args_array->data[i + 1]) + 1);
			strcpy(command->appends, args_array->data[i + 1]);

			DEBUG_SAY("Pop '%s' in args_array (%ld < %ld)\n", args_array->data[i], i, args_array->used_length);
			delete_string_from_array(i, args_array); // delete LINE_APPEND_STREAM_STRING
			delete_string_from_array(i, args_array); // delete argument
		}

		// The background running was set.
		else if (!strcmp(args_array->data[i], LINE_BACKGROUND_STRING))
		{
			command->is_in_background = 1;
			
			DEBUG_SAY("Pop %s in args_array (%ld < %ld)\n", args_array->data[i], i, args_array->used_length);
			delete_string_from_array(i, args_array); // delete LINE_BACKGROUND_STRING
		}

		i++;
	} // ENDWHILE (args_array->used_length)

	DEBUG_SAY("After while block\n");

	command->is_valid = is_valid;
	command->argc = args_array->used_length;
	command->argv = string_array_to_chars(args_array);

	DEBUG_SAY("After cmd call assignment:\n");
	DEBUG_SAY(" * Origin      : %s\n", command->origin);
	DEBUG_SAY(" * Ins         : %s\n", command->ins);
	DEBUG_SAY(" * Outs        : %s\n", command->outs);
	DEBUG_SAY(" * Appends     : %s\n", command->appends);
	DEBUG_SAY(" * In back     : %d\n", command->is_in_background);
	DEBUG_SAY(" * Valid       : %d\n", command->is_valid);
	DEBUG_SAY(" * ArgC        : %d\n", command->argc);
	DEBUG_SAY(" * ArgV (last) : %s\n", command->argv[command->argc - 1]);

	delete_string_array(args_array);
	
	DEBUG_END("done.");
	return command;
}


void clear_command(Cmd *command)
{
	if (command == NULL)
		return;

	DEBUG_START("Clearing the command call ...");

	int i;

	for (i = 0; i < command->argc; i++)
		free(command->argv[i]);

	command->argc = 0;
	
	free(command->argv);

	free(command->ins);
	free(command->outs);
	free(command->appends);
	free(command->origin);

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
