#include "main.h"

#include "debug.h"
#include "proc.h"


ProcessArray *get_process_array(int length)
{
	if (length < 1)
		length = 1;

	DEBUG_START("Creating the process array ...");

	ProcessArray *array = (ProcessArray*)malloc(sizeof(ProcessArray));

	array->data = (Process**)calloc(sizeof(Process*), length);
	array->allocated_length = length;
	array->used_length = 0;

	DEBUG_END("done.");

	return array;
}


void check_length_and_expand_process_array(ProcessArray *array)
{
	if ((array->allocated_length)
			> (array->used_length))
		return;

	if (array->allocated_length != 0)
		array->allocated_length *= PROCESS_ARRAY_EXPANDING_CRITERIA;
	else
		array->allocated_length = 1;
	
	Process **expanded_data = (Process**)calloc(sizeof(Process*), array->allocated_length);

	size_t i;
	for (i = 0; i < array->used_length; i++)
	{
		expanded_data[i] = (Process*)malloc(sizeof(Process));
//		expanded_data[i], array->data[i]);
		free(array->data[i]);
	}

	free(array->data);
	array->data = expanded_data;
}


void push_into_process_array(Process *proc, ProcessArray *array)
{
	if ((array == NULL)
			|| (proc == NULL))
		return;

	DEBUG_START("Pushing the process into array ...");
	
	check_length_and_expand_process_array(array);
	
	array->data[array->used_length] = proc;
	++array->used_length;

	DEBUG_END("done.");
}


void delete_process_from_array(size_t indx, ProcessArray *array)
{
	if ((array == NULL)
			|| (indx > array->used_length))
		return;

	DEBUG_START("Deleting the process from array ...");
	
	size_t i;

	for (i = indx; i < array->used_length - 1; i++)
		array->data[i] = array->data[i + 1];

	free(array->data[array->used_length - 1]);
	--array->used_length;

	DEBUG_END("done.");
}


void show_process_array(ProcessArray *array, FILE *stream)
{
	if (array == NULL)
		return;

	DEBUG_START("Showing the process array ...");
	
	// size_t i;

	// fprintf(stream, "[");

	// if (array->used_length != 0)
	// {
	// 	for (i = 0; i < array->used_length; i++)
	// 	{
	// 		fprintf(stream, "'%s', ", array->data[i]);
	// 	}

	// 	fprintf(stream, "\b\b");
	// }

	// fprintf(stream, "] (%ld, %ld)\n", array->used_length, array->allocated_length);

	DEBUG_END("done.");
}


void clear_process_array(ProcessArray *array)
{
	if (array == NULL)
		return;

	DEBUG_START("Clearing the process array ...");
	
	size_t i;

	for (i = 0; i < array->used_length; i++)
	{
		DEBUG_SAY("Process [%d] ", array->data[i]->pid);
		free(array->data[i]);
		DEBUG_SHOUT(" removed");
	}

	array->used_length = 0;

	DEBUG_END("done.");
}


void delete_process_array(ProcessArray *array)
{
	if (array == NULL)
		return;

	DEBUG_START("Deleting the process array ...");

	clear_process_array(array);

	free(array->data);
	free(array);

	DEBUG_END("done.");
}
