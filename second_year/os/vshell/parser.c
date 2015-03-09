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


CmdArguments *get_empty_command_call(char *cmd_name)
{
	if (cmd_name == NULL)
		return NULL;

	DEBUG_START("Creating the empty CmdArguments structure ...");
	
	CmdArguments *cmd_call = (CmdArguments*)malloc(sizeof(CmdArguments));
	cmd_call->origin = (char*)calloc(sizeof(char), strlen(cmd_name) + 1);
	cmd_call->ins = NULL;
	cmd_call->outs = NULL;
	cmd_call->appends = NULL;
	cmd_call->is_in_background = 0;
	cmd_call->args = NULL;

	strcpy(cmd_call->origin, cmd_name);
	
	DEBUG_END("done.");

	return cmd_call;
}


CmdArguments *get_command_call(char *line)
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
		return NULL;

	DEBUG_SAY("After if-else condition\n");

	// DEBUG_SHOW(args_array, show_string_array);

	// Setting up the CmdArguments structure.
	CmdArguments *cmd_call = get_empty_command_call(args_array->data[0]);
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

			delete_string_from_array(i, args_array);

			cmd_call->ins = (char*)calloc(sizeof(char), strlen(args_array->data[i + 1]) + 1);
			strcpy(cmd_call->ins, args_array->data[i + 1]);
		}

		// The output stream was set.
		else if (!strcmp(args_array->data[i], LINE_OUTPUT_STREAM_STRING))
		{
			if (i + 1 == args_array->used_length)
			{
				is_valid = 0;
				break;
			}

			delete_string_from_array(i, args_array);

			cmd_call->outs = (char*)calloc(sizeof(char), strlen(args_array->data[i + 1]) + 1);
			strcpy(cmd_call->outs, args_array->data[i + 1]);
		}

		// The append stream was set.
		else if (!strcmp(args_array->data[i], LINE_APPEND_STREAM_STRING))
		{
			if (i + 1 == args_array->used_length)
			{
				is_valid = 0;
				break;
			}
			
			delete_string_from_array(i, args_array);

			cmd_call->appends = (char*)calloc(sizeof(char), strlen(args_array->data[i + 1]) + 1);
			strcpy(cmd_call->appends, args_array->data[i + 1]);
		}

		// The background running was set.
		else if (!strcmp(args_array->data[i], LINE_BACKGROUND_STRING))
		{
			delete_string_from_array(i, args_array);

			cmd_call->is_in_background = 1;
		}

		i++;
	} // ENDWHILE

	cmd_call->is_valid = is_valid;
	cmd_call->args = args_array;
	
	DEBUG_END("done.");

	return cmd_call;
}


void show_command_call(CmdArguments *cmd_call, FILE *stream)
{
	if (cmd_call == NULL)
		return;

	DEBUG_START("Command call:");

	DEBUG_SAY("Origin: %s\n", cmd_call->origin);
	DEBUG_SAY("<       %s\n", cmd_call->ins);
	DEBUG_SAY(">       %s\n", cmd_call->outs);
	DEBUG_SAY(">>      %s\n", cmd_call->appends);
	DEBUG_SAY("&       %d\n", cmd_call->is_in_background);
	DEBUG_SAY("valid:  %d\n", cmd_call->is_valid);
	DEBUG_SAY("args: \n");
	// show_string_array(cmd_call->args, stream));
	
	DEBUG_END(".");
}


void clear_command_call(CmdArguments *cmd_call)
{
	if (cmd_call == NULL)
		return;

	delete_string_array(cmd_call->args);
}


int do_cmd(CmdArguments *call, CmdArray *cmds)
{
	if ((call == NULL)
		|| (call->origin == NULL))
	{
		// if (DEBUG)
		// 	printf("args is null ...\n");
		
		return CODE_WAIT;
	}

	DEBUG_START("Calling the command ...");
	// DEBUG_DO(show_command_call(call, stdout));

	if (!strcmp(call->origin, CMD_EXIT))
	{
		DEBUG_END("done.");
		return CODE_EXIT;
	}

	FILE *strin;
	FILE *strout;

	if (call->ins != NULL)
	{
		strin = fopen(call->ins, "r");
		
		if (strin == NULL)
		{
			printf("Cannot open input stream from %s file!\n", call->ins);

			DEBUG_END("done.");
			return CODE_FAIL;
		}
	}
	else
		strin = stdin;

	if (call->outs != NULL)
	{
		strout = fopen(call->outs, "w");
		
		if (strout == NULL)
		{
			printf("Cannot open output stream into %s file!\n", call->outs);

			DEBUG_END("done.");
			return CODE_FAIL;
		}
	}
	else if (call->appends != NULL)
	{
		strout = fopen(call->appends, "r+");
		
		if (strout == NULL)
		{
			printf("Cannot open append stream into %s file!\n", call->appends);

			DEBUG_END("done.");
			return CODE_FAIL;
		}
	}
	else
		strout = stdout;

	size_t i;

	for (i = 0; i < cmds->used_length; i++)
	{
		if (!strcmp(call->origin, (cmds->data[i])->name))
		{
			DEBUG_END("done.");
			return ((cmds->data[i])->func)(strin, strout, call->args);
		}
	}

	DEBUG_END("done.");
	return CODE_UNKNOWN_CMD;
}
