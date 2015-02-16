#ifndef __HISTORY_H__
#define __HISTORY_H__


typedef struct StringArray
{
	size_t allocated_length;
	size_t used_length;
	char **data;
} StringArray;


StringArray *get_array(int length);
void check_length_and_expand_array(StringArray *array);
void push_into_array(char *string, StringArray *array);
void show_array(StringArray *array);


// __HISTORY_H__
#endif