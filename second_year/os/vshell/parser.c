#include "main.h"

#include "debug.h"
#include "array.h"
#include "cmd.h"
#include "parser.h"


StringArray *split(char *line)
{
	if ((line == NULL)
		|| (line == 0)
		|| ((*line) == LINE_END_SYMBOL))
	{
		printf("Invalid line while splitting %s\n", line);

		return NULL;
	}

	DEBUG_START("Splitting the line of chars by spaces ...");

	StringArray *array = get_string_array(2);
	char *chr = line;
	char data[LINE_LEN];
	bzero(data, LINE_LEN);

	int data_len = 0;
	int is_string = 0;

	while ((*chr) != 0)
	{
		if ((!is_string)
			&& ((*chr) == LINE_DELIMITTER_SYMBOL))
		{
			is_string = 1;
		}
		
		else if (((is_string)
				&& ((*chr) == LINE_DELIMITTER_SYMBOL))
			|| ((!is_string)
				&& (((*chr) == LINE_SEPARATOR_SYMBOL)
					|| ((*chr) == LINE_TAB_SYMBOL)
					|| ((*chr) == LINE_END_SYMBOL))))
		{
			if (data_len != 0)
			{
				DEBUG_SAY("pushing data: '%s'\n", data);
			
				push_into_string_array(data, array);

				bzero(data, LINE_LEN);
				data_len = 0;
				is_string = 0;
			}
		}

		else if ((*chr) == LINE_SKIP_SYMBOL)
		{
			data[data_len++] = (*(++chr));
		}

		else
			data[data_len++] = (*chr);
		
		chr++;
	}

	DEBUG_END("done.");

	return array;
}


Call *get_empty_command_call(char *cmd_name)
{
	if (cmd_name == NULL)
		return NULL;

	DEBUG_START("Creating the empty Call structure ...");
	
	Call *cmd_call = (Call*)malloc(sizeof(Call));
	cmd_call->origin = (char*)calloc(sizeof(char), strlen(cmd_name) + 1);
	cmd_call->ins = NULL;
	cmd_call->outs = NULL;
	cmd_call->appends = NULL;
	cmd_call->is_in_background = 0;
	cmd_call->argv = NULL;

	strcpy(cmd_call->origin, cmd_name);
	
	DEBUG_END("done.");

	return cmd_call;
}


Call *get_command_call(char *line)
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

	// Setting up the Call structure.
	Call *cmd_call = get_empty_command_call(args_array->data[0]);

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

			cmd_call->ins = (char*)calloc(sizeof(char), strlen(args_array->data[i + 1]) + 1);
			strcpy(cmd_call->ins, args_array->data[i + 1]);

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

			cmd_call->outs = (char*)calloc(sizeof(char), strlen(args_array->data[i + 1]) + 1);
			strcpy(cmd_call->outs, args_array->data[i + 1]);

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
			
			cmd_call->appends = (char*)calloc(sizeof(char), strlen(args_array->data[i + 1]) + 1);
			strcpy(cmd_call->appends, args_array->data[i + 1]);

			DEBUG_SAY("Pop '%s' in args_array (%ld < %ld)\n", args_array->data[i], i, args_array->used_length);
			delete_string_from_array(i, args_array); // delete LINE_APPEND_STREAM_STRING
			delete_string_from_array(i, args_array); // delete argument
		}

		// The background running was set.
		else if (!strcmp(args_array->data[i], LINE_BACKGROUND_STRING))
		{
			cmd_call->is_in_background = 1;
			
			DEBUG_SAY("Pop %s in args_array (%ld < %ld)\n", args_array->data[i], i, args_array->used_length);
			delete_string_from_array(i, args_array); // delete LINE_BACKGROUND_STRING
		}

		i++;
	} // ENDWHILE (args_array->used_length)

	DEBUG_SAY("After while block\n");

	cmd_call->is_valid = is_valid;
	cmd_call->argc = args_array->used_length;
	cmd_call->argv = string_array_to_chars(args_array);

	DEBUG_SAY("After cmd call assignment:\n");
	DEBUG_SAY(" * Origin      : %s\n", cmd_call->origin);
	DEBUG_SAY(" * Ins         : %s\n", cmd_call->ins);
	DEBUG_SAY(" * Outs        : %s\n", cmd_call->outs);
	DEBUG_SAY(" * Appends     : %s\n", cmd_call->appends);
	DEBUG_SAY(" * In back     : %d\n", cmd_call->is_in_background);
	DEBUG_SAY(" * Valid       : %d\n", cmd_call->is_valid);
	DEBUG_SAY(" * ArgC        : %d\n", cmd_call->argc);
	DEBUG_SAY(" * ArgV (last) : %s\n", cmd_call->argv[cmd_call->argc - 1]);

	delete_string_array(args_array);
	
	DEBUG_END("done.");
	return cmd_call;
}


void clear_command_call(Call *cmd_call)
{
	if (cmd_call == NULL)
		return;

	DEBUG_START("Clearing the command call ...");

	int i;

	for (i = 0; i < cmd_call->argc; i++)
		free(cmd_call->argv[i]);

	cmd_call->argc = 0;
	
	free(cmd_call->argv);

	free(cmd_call->ins);
	free(cmd_call->outs);
	free(cmd_call->appends);
	free(cmd_call->origin);

	DEBUG_END("done.");
}


void delete_command_call(Call *cmd_call)
{
	if (cmd_call == NULL)
		return;

	DEBUG_START("Deleting the command call ...");

	clear_command_call(cmd_call);
	free(cmd_call);

	DEBUG_END("done.");
}
