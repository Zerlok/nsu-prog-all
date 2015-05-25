#ifndef __PROC_H__
#define __PROC_H__


typedef struct Process
{
	// Name of the process.
	char *name;

	// The next process in group.
	struct Process *next;

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
	int status;
} Process;

Process *create_process(char *name);
void show_process(Process *proc);
void clear_process(Process *proc);
void delete_process(Process *proc);


typedef struct ProcessGroup
{
	pid_t pgid;
	Process *head;
	struct ProcessGroup *next_group;
	struct termios *term_modes;
} ProcessGroup;

ProcessGroup *create_process_group(pid_t pgid);
void push_process_in_group(Process *proc, ProcessGroup *group);
int remove_process_from_group(pid_t pid, ProcessGroup *group);
void show_process_group(ProcessGroup *group);
void clear_process_group(ProcessGroup *group);
void delete_process_group(ProcessGroup *group);


typedef struct ProcessList
{
	ProcessGroup *first;
} ProcessList;

ProcessList *create_process_list();
Process *find_process_in_list(pid_t pid, ProcessList *list);
void push_process_into_list(Process *proc, ProcessList *list);
int remove_process_from_list(pid_t pid, ProcessList *list);
ProcessGroup *find_process_group_in_list(pid_t pgid, ProcessList *list);
void push_process_group_into_list(ProcessGroup *group, ProcessList *list);
int remove_process_group_from_list(pid_t pgid, ProcessList *list);
void show_process_list(ProcessList *list);
void clear_process_list(ProcessList *list);
void delete_process_list(ProcessList *list);


int was_process_group_stopped(ProcessGroup *group);
int was_process_group_completed(ProcessGroup *group);


// __PROC_H__
#endif
