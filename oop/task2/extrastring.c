#include <stdio.h>
#include <string.h>

#include "extrastring.h"


void string_printor(void *ptr)
{
	printf("%s ", (
			(ptr != NULL) ? (char*)ptr : ""
	));
}


char *str_get(String *strings, size_t idx)
{
	return ((char*)(ra_get(strings, idx)));
}


void (*str_print)(RecordArray *strings) = ra_print;
void (*str_delete)(RecordArray *strings) = ra_delete;


int str_count(char *string, char chr)
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


String *str_split(char *string, char *chr)
{
	int chrnum = str_count(string, *chr);
	String *strarr = ra_create(chrnum+1, sizeof(char*));
	strarr->f_element_printor = str_print;

	char *substr = strtok(string, chr);
	int i;
	for (i = 0; ((substr != NULL) && (i < chrnum+1)); i++)
	{
		ra_set(strarr, i, substr);
		substr = strtok(NULL, chr);
	}

	return strarr;
}
