#ifndef __PROC_H__
#define __PROC_H__


typedef struct Process
{
	// Name of the process.
	char *name;

	// Process id, process group id
	pid_t pid;
	pid_t pgid;

	// Input, Output, Erro descriptors
	int in_fileno;
	int out_fileno;
	int err_fileno;

	// Process state.
	int is_stopped;
	int is_completed;
	int is_in_bg;
} Process;

Process *create_process(char *name);
void show_process(Process *proc);
void clear_process(Process *proc);
void delete_process(Process *proc);


typedef struct ProcessArray
{
	size_t allocated_length;
	size_t used_length;
	Process **data;
} ProcessArray;

ProcessArray *create_process_array(int length);
void check_length_and_expand_process_array(ProcessArray *array);
void push_into_process_array(Process *proc, ProcessArray *array);
Process *pop_process_from_array(size_t indx, ProcessArray *array);
void show_process_array(ProcessArray *array);
void clear_process_array(ProcessArray *array);
void delete_process_array(ProcessArray *array);


// __PROC_H__
#endif
