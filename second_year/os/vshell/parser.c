#include "main.h"

#include "debug.h"
#include "array.h"
#include "proc.h"
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

	StringArray *array = get_string_array(1);
	char *chr = line;
	char symbol[2];
	bzero(symbol, 2);
	char data[LINE_LEN];
	bzero(data, LINE_LEN);

	int data_len = 0;
	int is_string = 0;

	// TODO: make echo hi>>hello splittable!
	while ((*chr) != 0)
	{
		// Start string if it was not started and this char is a delimitter.
		if ((!is_string)
				&& ((*chr) == LINE_DELIMITTER_SYMBOL))
			is_string = 1;

		// Split if:
		//    * String ends with delemitter.
		//    * Separator or tab or line end was found without delimitter.
		else if (((is_string)
				  && ((*chr) == LINE_DELIMITTER_SYMBOL))
				 || ((!is_string)
					 && (((*chr) == LINE_SEPARATOR_SYMBOL)
						 || ((*chr) == LINE_TAB_SYMBOL)
						 || ((*chr) == LINE_END_SYMBOL))))
			SAVE_DATA;

		// Split and save redirecting symbol if this char not in string
		// and it is one of shell redirecting symbols.
		else if ((!is_string)
				 && (((*chr) == LINE_INPUT_STREAM_STRING[0])
					 || ((*chr) == LINE_OUTPUT_STREAM_STRING[0])
					 || ((*chr) == LINE_APPEND_STREAM_STRING[0])
					 || ((*chr) == LINE_BACKGROUND_STRING[0])
					 || ((*chr) == LINE_PIPE_STRING[0])))
		{
			SAVE_DATA;

			if ((*(chr + 1)) != LINE_APPEND_STREAM_STRING[1])
			{
				symbol[0] = (*chr);
				symbol[1] = 0;

				push_into_string_array(symbol, array);
			}
			else
			{
				push_into_string_array(LINE_APPEND_STREAM_STRING, array);
				++chr;
			}
		}

		// Add next char to string if this char is a skipper.
		else if ((*chr) == LINE_SKIPPER_SYMBOL)
			data[data_len++] = (*(++chr));

		// Add this char to string.
		else
			data[data_len++] = (*chr);
		
		++chr;
	}

	DEBUG_END("done.");
	return array;
}
