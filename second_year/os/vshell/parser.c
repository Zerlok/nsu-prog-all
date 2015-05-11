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

	DEBUG_START("Splitting the line of chars by spaces and special symbols ...");

	StringArray *array = get_string_array(2);
	char *chr = line;
	char data[LINE_LEN];
	bzero(data, LINE_LEN);

	int data_len = 0;
	int is_string = 0;

	// TODO: make echo hi>>hello splittable!
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
