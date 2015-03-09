#include "main.h"

#include "debug.h"
#include "array.h"


StringArray *get_string_array(int length)
{
	if (length < 1)
		length = 1;

	DEBUG_START("Creating the string array ...");

	StringArray *array = (StringArray*)malloc(sizeof(StringArray));

	array->data = (char**)calloc(sizeof(char*), length);
	array->allocated_length = length;
	array->used_length = 0;

	DEBUG_END("done.");

	return array;
}


void check_length_and_expand_string_array(StringArray *array)
{
	if ((array->allocated_length)
		< (array->used_length))
		return;
	
	array->allocated_length *= STRING_ARRAY_EXPANDING_CRITERIA;
	array->data = (char**)realloc(array->data, array->allocated_length);
}


void push_into_string_array(char *string, StringArray *array)
{
	if ((array == NULL)
		|| (string == NULL))
		return;

	DEBUG_START("Pushing the string into string array ...");
	
	check_length_and_expand_string_array(array);
	
	array->data[array->used_length] = (char*)calloc(sizeof(char), strlen(string) + 1);
	strcpy(array->data[array->used_length], string);
	
	array->used_length++;

	DEBUG_END("done.");
}


void delete_string_from_array(size_t indx, StringArray *array)
{
	if ((array == NULL)
		|| (indx > array->used_length)
		|| (indx < 0))
		return;

	DEBUG_START("Deleting the string from string array ...");
	
	int i;

	for (i = indx; i < array->used_length - 1; i++)
	{
		array->data[i] = (char*)realloc(array->data[i], strlen(array->data[i + 1]) + 1);
		strcpy(array->data[i + 1], array->data[i]);
	}

	free(array->data[array->used_length]);
	array->used_length--;

	DEBUG_END("done.");
}


void show_string_array(StringArray *array, FILE *stream)
{
	if (array == NULL)
		return;

	DEBUG_START("Showing the string array ...");
	
	size_t i;

	fprintf(stream, "[");

	if (array->used_length != 0)
	{
		for (i = 0; i < array->used_length; i++)
		{
			fprintf(stream, "'%s', ", array->data[i]);
		}

		fprintf(stream, "\b\b");
	}

	fprintf(stream, "] (%ld, %ld)\n", array->used_length, array->allocated_length);

	DEBUG_END("done.");
}


void clear_string_array(StringArray *array)
{
	if (array == NULL)
		return;

	DEBUG_START("Clearing the string array ...");
	
	size_t i;

	for (i = 0; i < array->used_length; i++)
		free(array->data[i]);

	array->used_length = 0;

	DEBUG_END("done.");
}


void delete_string_array(StringArray *array)
{
	if (array == NULL)
		return;

	DEBUG_START("Deleting the string array ...");

	clear_string_array(array);

	free(array->data);

	DEBUG_END("done.");
}