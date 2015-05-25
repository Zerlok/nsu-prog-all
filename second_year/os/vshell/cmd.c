#include "main.h"
#include "array.h"
#include "cmd.h"
#include "parser.h"


Cmd *create_empty_command(char *cmd_name)
{
	if (cmd_name == NULL)
		return NULL;

	DEBUG_START("Creating an empty command ...");
	
	Cmd *command = (Cmd*)malloc(sizeof(Cmd));

	command->ins = NULL;
	command->outs = NULL;
	command->appends = NULL;
	command->errs = NULL;
	command->pipe = NULL;
	command->argv = NULL;
	command->argc = 0;
	clear_command(command);

	command->origin = (char*)calloc(sizeof(char), strlen(cmd_name) + 1);
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

	// Splitting the line by spaces.
	StringArray *splitted_line = split(line);
	DEBUG_SAY("After splitting\n");

	if ((splitted_line == NULL)
			|| (splitted_line->used_length == 0))
	{
		delete_string_array(splitted_line);
		DEBUG_END("failed (empty split).");
		return NULL;
	}
	DEBUG_SAY("After if-else condition\n");

	// Setting up the Cmd structure.
	Cmd *main_command = create_empty_command(splitted_line->data[0]);
	Cmd *command = main_command;
	StringArray *command_args = get_string_array(1);
	DEBUG_SAY("After empty command creation\n");

	size_t i = 0;
	int is_valid = 1; // (true)
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

			// Save current arguments.
			command->argc = command_args->used_length;
			command->argv = get_string_array_data(command_args);
			DEBUG_SAY("Current cmd: ");
			DEBUG_SHOW_CMD(command);

			// Create a new command in pipe.
			command->pipe = create_empty_command(splitted_line->data[i + 1]);
			clear_string_array(command_args);

			command = command->pipe;
		}

		// The clean argument was found -> push it into cmd argv
		else
			push_into_string_array(
					splitted_line->data[i],
					command_args
			);

		++i;
	} // ENDWHILE (splitted_line->used_length)

	main_command->is_valid = is_valid;
	command->is_valid = is_valid;
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

	DEBUG_START("Clearing the command ...");

	DEBUG_SAY("Removing origin ...\n");
	free(command->origin);
	DEBUG_SAY("Removing ins ...\n");
	free(command->ins);
	DEBUG_SAY("Removing outs ...\n");
	free(command->outs);
	DEBUG_SAY("Removing appends ...\n");
	free(command->appends);
	DEBUG_SAY("Removing errs ...\n");
	free(command->errs);
	DEBUG_SAY("Removing pipe ...\n");
	delete_command(command->pipe);

	DEBUG_SAY("Removing argv ...\n");
	int i;
	for (i = 0; i < command->argc; i++)
		free(command->argv[i]);
	free(command->argv);

	command->origin = NULL;
	command->ins = NULL;
	command->outs = NULL;
	command->appends = NULL;
	command->errs = NULL;
	command->pipe = NULL;
	command->argv = NULL;
	command->argc = 0;
	command->is_valid = 0;
	command->is_in_background = 0;

	DEBUG_END("done.");
}


void delete_command(Cmd *command)
{
	if (command == NULL)
		return;

	DEBUG_START("Deleting the command ...");

	clear_command(command);
	free(command);

	DEBUG_END("done.");
}
