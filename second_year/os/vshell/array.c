#include "main.h"
#include "array.h"


StringArray *get_array(int length)
{
	if (length < 1)
		length = 1;

	printf("Creating the array...\n");

	StringArray *array = (StringArray*)malloc(sizeof(StringArray));

	array->data = (char**)calloc(sizeof(char*), length);
	array->allocated_length = length;
	array->used_length = 0;

	return array;
}


void check_length_and_expand_array(StringArray *array)
{
	if ((array->allocated_length)
		== (array->used_length))
	{
		array->allocated_length *= ARRAY_EXPANDING_CRITERIA;
		array->data = (char**)realloc(array->data, array->allocated_length);
	}
}


void push_into_array(char *string, StringArray *array)
{
	if (string != NULL)
	{
		check_length_and_expand_array(array);
		
		array->data[array->used_length] = (char*)calloc(sizeof(char), strlen(string));
		strcpy(array->data[array->used_length], string);
		
		array->used_length++;
	}
}


void show_array(StringArray *array)
{
	size_t i;

	printf("[");

	if (array->used_length != 0)
	{
		for (i = 0; i < array->used_length; i++)
		{
			printf("'%s', ", array->data[i]);
		}

		printf("\b\b");
	}

	printf("] (%ld, %ld)\n", array->used_length, array->allocated_length);
}


void clear_array(StringArray *array)
{
	size_t i;

	for (i = 0; i < array->used_length; i++)
		free(array->data[i]);

	array->used_length = 0;
}


void delete_array(StringArray *array)
{
	clear_array(array);

	free(array->data);
}