#include <stdio.h>
#include <stdlib.h>
#include "longstring.h"


t_longstring *get_longstring(char *data)
{
	if (data == NULL)
		return NULL;

	t_longstring *longstring = (t_longstring*)malloc(sizeof(t_longstring));
	longstring->m_data = (char*)calloc(sizeof(char), _LONGSTRING_EXPAND_CRITERIA);
	longstring->m_size = _LONGSTRING_EXPAND_CRITERIA;
	longstring->m_index = 0;

	unsigned long long int i = 0;
	while (data[i] != 0)
	{
		append_longstring(longstring, data[i]);
		++i;
	}

	return longstring;
}


void check_and_expand_longstring(t_longstring *longstring)
{
	while (longstring->m_index >= longstring->m_size - 1)
	{
		longstring->m_size *= _LONGSTRING_EXPAND_CRITERIA;
		longstring->m_data = (char*)realloc(longstring->m_data, longstring->m_size);
	}
}


void append_longstring(t_longstring *longstring, char chr)
{
	check_and_expand_longstring(longstring);

	longstring->m_data[longstring->m_index] = chr;
	(longstring->m_index)++;
	longstring->m_data[longstring->m_index] = 0;
}


int is_endswith_longstring(t_longstring *working_string, t_longstring *comparing_string)
{
	unsigned long long int i;

	if (comparing_string->m_index > working_string->m_index)
		return 0;

	unsigned long long int delta = (working_string->m_index - comparing_string->m_index);
	for (i = delta; i < working_string->m_index; i++)
		if (working_string->m_data[i] != comparing_string->m_data[i - delta])
			return 0;

	return 1;
}


void print_longstring(t_longstring *longstring)
{
	unsigned long long int i;
	for (i = 0; i < longstring->m_index; i++)
		printf("%c", longstring->m_data[i]);

	printf("\n");
}


void destroy_longstring(t_longstring *longstring)
{
	if (longstring == NULL)
		return;

	free(longstring->m_data);
	free(longstring);
}
