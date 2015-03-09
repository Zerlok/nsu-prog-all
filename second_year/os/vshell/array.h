#ifndef __HISTORY_H__
#define __HISTORY_H__


typedef struct StringArray
{
	size_t allocated_length;
	size_t used_length;
	char **data;
} StringArray;


StringArray *get_string_array(int length);
void check_length_and_expand_string_array(StringArray *array);
void push_into_string_array(char *string, StringArray *array);
void delete_string_from_array(size_t indx, StringArray *array);
void show_string_array(StringArray *array, FILE *stream);
void clear_string_array(StringArray *array);
void delete_string_array(StringArray *array);


// __HISTORY_H__
#endif