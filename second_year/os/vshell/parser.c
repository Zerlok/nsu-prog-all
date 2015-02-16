#include "main.h"

#include "array.h"
#include "cmd.h"
#include "parser.h"


void clear_string(char *string, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++)
		string[i] = '\0';
}


void split_line_to_args(char *line, StringArray *args)
{
	printf("Splitting the line...\n");
	size_t i;
	size_t arg_len = 0;
	size_t length = strlen(line);

	char arg[LINE_BUFF];
	clear_string(arg, LINE_BUFF);

	for (i = 0; i < length; i++)
	{
		if ((line[i] == LINE_SEPARATOR)
			|| (line[i] == LINE_END))
		{
			printf("\t pushing %s\n", arg);
			push_into_array(arg, args);
			clear_string(arg, LINE_BUFF);
			arg_len = 0;
		}
		else if (arg_len < LINE_BUFF)
		{
			arg[arg_len] = line[i];
			arg_len++;
		}
	}
}


int parse_cmd(char *line, Commands *cmds)
{
	if ((line == NULL)
		|| line[0] == LINE_END)
		return CODE_WAIT;

	StringArray *args = get_array(256);

	split_line_to_args(line, args);

	show_array(args);

	if (!strcmp(args->data[0], (cmds->data[0])->name))
		return CODE_EXIT;

	size_t i;

	for (i = 1; i < cmds->used_length; i++)
	{
		if (!strcmp(args->data[0], (cmds->data[i])->name))
		{
			((cmds->data[i])->func)();

			return 0;
		}
	}

	return CODE_UNKNOWN_CMD;
}
