#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "extrastring.h"


void (*sa_print)(StringArray *strings) = ra_print;
void (*sa_delete)(StringArray *strings) = ra_delete;


void string_printor(void *ptr)
{
	RecordArray *string  = ptr;
	char *text = (string != NULL)
			? string->m_data
			: NULL;

	if (text != NULL)
		printf("'%s' ", text);

	else
		printf("(null) ");
}


StringArray *sa_create(size_t size)
{
	StringArray *self = ra_create(size, sizeof(RecordArray));
	self->f_element_printor = string_printor;

	return self;
}


char *sa_get(StringArray *strings, size_t idx)
{
	RecordArray *data = ra_get(strings, idx);
	if (data == NULL)
		return NULL;

	return ((char*)(data->m_data));
}


void sa_set(StringArray *strings, size_t idx, char *string)
{
	RecordArray *data = ra_get(strings, idx);
	if (data == NULL)
		return;

	free(data->m_data);
	data->m_data = (char*)calloc(strlen(string)+1, sizeof(char));
	strcpy(data->m_data, string);
}




int count_chars(char *string, char chr)
{
	if (string == NULL)
		return 0;

	int counter = 0;

	int i;
	for (i = 0; string[i] != 0; i++)
		if (string[i] == chr)
			++counter;

	return counter;
}


StringArray *str_split(char *string, char *chr)
{
	int chrnum = count_chars(string, *chr);
	StringArray *strarr = sa_create(chrnum+1);

	char *substr = strtok(string, chr);
	int i;
	for (i = 0; ((substr != NULL) && (i < chrnum+1)); i++)
	{
		sa_set(strarr, i, substr);
		substr = strtok(NULL, chr);
	}

	return strarr;
}
