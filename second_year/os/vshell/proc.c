#include "main.h"
#include "proc.h"


Process *create_process(char *name)
{
	DEBUG_START("Creating the process ...");

	Process *proc = (Process*)malloc(sizeof(Process));
	proc->name = NULL;
	clear_process(proc);

	// Assign the name.
	proc->name = (char*)calloc(sizeof(char), strlen(name) + 1);
	strcpy(proc->name, name);

	DEBUG_END("done.");
	return proc;
}


void show_process(Process *proc)
{
	printf("[%d : %d]\t\t%s\t%s%s%s\n",
			proc->pid,
			proc->pgid,
			proc->name,
			proc->is_stopped ? "stopped " : "",
			proc->is_completed ? "completed" : "",
			proc->is_in_bg? "bg" : "fg"
	);
}


void clear_process(Process *proc)
{
	DEBUG_START("Clearing the process ...");

	proc->pid = 0;
	proc->pgid = 0;
	proc->in_fileno = -1;
	proc->out_fileno = -1;
	proc->err_fileno = -1;
	proc->is_stopped = 0;
	proc->is_completed = 0;
	proc->is_in_bg = 0;
	free(proc->name);

	DEBUG_END("done.");
}


void delete_process(Process *proc)
{
	DEBUG_START("Deleting the process ...");

	clear_process(proc);
	free(proc);

	DEBUG_END("done.");
}


ProcessArray *create_process_array(int length)
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
		expanded_data[i] = array->data[i];

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


Process *pop_process_from_array(size_t indx, ProcessArray *array)
{
	if ((array == NULL)
			|| (indx > array->used_length))
		return NULL;

	DEBUG_START("Deleting the process from array ...");
	
	Process *element = array->data[indx];

	size_t i;
	for (i = indx; i < array->used_length - 1; i++)
		array->data[i] = array->data[i + 1];

	array->data[array->used_length - 1] = NULL;
	--array->used_length;

	DEBUG_END("done.");
	return element;
}


void show_process_array(ProcessArray *array)
{
	if ((array == NULL)
			|| (array->used_length == 0))
		return;

	DEBUG_START("Showing the process array ...");
	printf("Processes %ld:\n", array->used_length, array->allocated_length);

	size_t i;
	for (i = 0; i < array->used_length; i++)
	{
		printf("\t");
		show_process(array->data[i]);
	}

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
