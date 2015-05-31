#include "main.h"

#include "array.h"
#include "cmd.h"
#include "parser.h"


void split_line_to_args(char *line, StringArray *args)
{
	printf("Splitting the line...\n");
	size_t i;
	size_t arg_len = 0;
	size_t length = strlen(line);

	char arg[LINE_BUFF];
	bzero(arg, LINE_BUFF);

	for (i = 0; i < length; i++)
	{
		if ((line[i] == LINE_SEPARATOR)
			|| (line[i] == LINE_END))
		{
			printf("\t pushing '%s' into args...\n", arg);
			push_into_array(arg, args);
			bzero(arg, LINE_BUFF);
			arg_len = 0;
		}
		else if (arg_len < LINE_BUFF)
		{
			arg[arg_len] = line[i];
			arg_len++;
		}
	}
}


int do_cmd(StringArray *args, Commands *cmds)
{
	if ((args == NULL)
		|| (args->data == NULL)
		|| (args->data[0] == NULL)
		|| (args->data[0][0] == '\0')
		|| (args->data[0][0] == LINE_SEPARATOR)
		|| (args->data[0][0] == LINE_END))
		return CODE_WAIT;

	show_array(args);

	if (!strcmp(args->data[0], (cmds->data[0])->name))
	{
		((cmds->data[0])->func)();

		return CODE_EXIT;
	}

	size_t i;

	for (i = 1; i < cmds->used_length; i++)
	{
		if (!strcmp(args->data[0], (cmds->data[i])->name))
		{
			((cmds->data[i])->func)();

			return CODE_SUCCESS;
		}
	}

	return CODE_UNKNOWN_CMD;
}
