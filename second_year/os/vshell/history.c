#include "main.h"
#include "history.h"


History *get_history(int length)
{
	History *history = (History*)malloc(sizeof(History));

	history->data = (char**)calloc(sizeof(char*), length);
	history->allocated_length = length;
	history->used_length = 0;

	return history;
}


void check_length_and_expand_history(History *history)
{
	if ((history->allocated_length)
		== (history->used_length))
	{
		history->allocated_length *= HISTORY_EXPANDING_CRITERIA;
		history->data = (char**)realloc(history->data, history->allocated_length);
	}
}


void push_into_history(char *string, History *history)
{
	check_length_and_expand_history(history);
	
	(history->data)[(history->used_length)++] = string;
}


void show_history(History *history)
{
	size_t i;

	printf("[");

	if (history->used_length != 0)
	{
		for (i = 0; i < history->used_length; i++)
		{
			printf("%s, ", history->data[i]);
		}

		printf("\b\b");
	}

	printf("] (%ld, %ld)\n", history->used_length, history->allocated_length);
}
