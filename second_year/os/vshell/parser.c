#include "main.h"

#include "array.h"
#include "cmd.h"
#include "parser.h"


void split_line_to_args(char *line, StringArray *args)
{
	printf("Splitting the line...\n");

	// Initializing the variables...
	size_t i = 0;
	size_t arg_len = 0;
	size_t length = strlen(line);

	char arg[LINE_BUFF];
	// StringArray *args = get_array(10);

	int is_valid = 1;
	int is_string = 0;

	while ((i < length)
		&& (is_valid))
	{
		switch (line[i])
		{
			case LINE_DELIMITTER_SYMBOL:
			{
				is_string = !is_string;
				break;
			}

			case LINE_INPUT_STREAM_SYMBOL:
			{
				if ((arg_len != 0)
					&& (!is_string))
				{
					is_valid = 0;
					break;
				}

				break;
			}

			case LINE_SEPARATOR_SYMBOL:
			case LINE_END_SYMBOL:
			{
				printf("\t pushing '%s' into args...\n", arg);
				push_into_array(arg, args);
				bzero(arg, LINE_BUFF);
				arg_len = 0;

				break;
			}

			// If this symbol is not special.
			default:
			{
				if (arg_len < LINE_BUFF)
				{
					arg[arg_len] = line[i];
					arg_len++;
				}

				break;
			}
		} // ENDSWITCH

		i++;
	} // ENDWHILE	
}


int do_cmd(StringArray *args, Commands *cmds)
{
	if ((args == NULL)
		|| (args->data == NULL)
		|| (args->data[0] == NULL)
		|| (args->data[0][0] == 0)
		|| (args->data[0][0] == LINE_SEPARATOR_SYMBOL)
		|| (args->data[0][0] == LINE_END_SYMBOL))
	{
		printf("args is null, waiting for the next command ...\n");
		return CODE_WAIT;
	}

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
