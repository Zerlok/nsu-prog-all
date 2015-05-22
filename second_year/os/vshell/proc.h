#ifndef __PROC_H__
#define __PROC_H__


typedef struct Process
{
	pid_t pid;
	pid_t gid;
	int is_stopped;
	int is_finished;
	int is_in_background;
} Process;

Process *create_process(int pid);
void show_process(Process *proc);
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
void show_process_array(ProcessArray *array, FILE *stream);
void clear_process_array(ProcessArray *array);
void delete_process_array(ProcessArray *array);


// __PROC_H__
#endif
