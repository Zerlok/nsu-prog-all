#include "main.h"

#include "array.h"
#include "cmd.h"
#include "parser.h"


StringArray *split(char *line)
{
	if ((line == NULL)
		|| (line == 0)
		|| ((*line) == LINE_END_SYMBOL))
	{
		printf("Invalid line while splitting %p\n", line);

		return NULL;
	}

	if (DEBUG)
		printf("\nSplitting the '%s' line of chars by spaces ...\n", line);

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
				if (DEBUG)
					printf("\t pushing data: '%s'\n", data);
			
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

	if (DEBUG)
		printf("done.\n");

	return array;
}


CmdArguments *get_empty_command_call(char *cmd_name)
{
	if (cmd_name == NULL)
		return NULL;

	if (DEBUG)
		printf("\nCreating the empty CmdArguments structure ... ");
	
	CmdArguments *cmd_call = (CmdArguments*)malloc(sizeof(CmdArguments));
	cmd_call->origin = (char*)calloc(sizeof(char), strlen(cmd_name) + 1);
	cmd_call->ins = NULL;
	cmd_call->outs = NULL;
	cmd_call->appends = NULL;
	cmd_call->is_in_background = 0;
	cmd_call->args = NULL;

	strcpy(cmd_call->origin, cmd_name);
	
	if (DEBUG)
		printf("done.\n");

	return cmd_call;
}


CmdArguments *get_command_call(char *line)
{
	if ((line == NULL)
		|| (line == 0)
		|| ((*line) == LINE_END_SYMBOL))
		return NULL;

	printf("\nCreating a new command call ... \n");

	// Initializing the variables...
	size_t i = 0;
	int is_valid = 1; // (true)

	// Splitting the line by spaces.
	StringArray *args_array = split(line);

	if (DEBUG)
	{
		printf("Splitted line: \n");
		show_string_array(args_array, stdout);
	}

	// Setting up the CmdArguments structure.
	CmdArguments *cmd_call = get_empty_command_call(args_array->data[0]);

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
	
	if (DEBUG)
		printf("done.\n");

	return cmd_call;
}


void show_command_call(CmdArguments *cmd_call, FILE *stream)
{
	if (cmd_call == NULL)
		return;

	fprintf(stream, "Origin: %s\n", cmd_call->origin);
	fprintf(stream, " <       %s\n", cmd_call->ins);
	fprintf(stream, " >       %s\n", cmd_call->outs);
	fprintf(stream, " >>      %s\n", cmd_call->appends);
	fprintf(stream, " &       %d\n", cmd_call->is_in_background);
	fprintf(stream, " valid:  %d\n", cmd_call->is_valid);
	fprintf(stream, " args: ");
	show_string_array(cmd_call->args, stream);	
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

	if (DEBUG)
	{
		printf("\nCalling the command:\n");
		show_command_call(call, stdout);
	}

	if (!strcmp(call->origin, CMD_EXIT))
		return CODE_EXIT;

	FILE *strin;
	FILE *strout;

	if (call->ins != NULL)
	{
		strin = fopen(call->ins, "r");
		
		if (strin == NULL)
		{
			printf("Cannot open input stream from %s file!\n", call->ins);

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

			return CODE_FAIL;
		}
	}
	else if (call->appends != NULL)
	{
		strout = fopen(call->appends, "r+");
		
		if (strout == NULL)
		{
			printf("Cannot open append stream into %s file!\n", call->appends);

			return CODE_FAIL;
		}
	}
	else
		strout = stdout;

	size_t i;

	for (i = 1; i < cmds->used_length; i++)
	{
		if (!strcmp(call->origin, (cmds->data[i])->name))
			return ((cmds->data[i])->func)(strin, strout, call->args);
	}

	return CODE_UNKNOWN_CMD;
}
