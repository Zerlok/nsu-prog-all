#include "main.h"
#include "proc.h"


// ------------------- PROCESS ------------------- //

Process *create_process(char *name)
{
	DEBUG_START("Creating the process ...");

	Process *proc = (Process*)malloc(sizeof(Process));
	proc->name = NULL;
	proc->next = NULL;
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
			proc->pgid,
			proc->pid,
			proc->name,
			proc->is_stopped ? "stopped " : "",
			proc->is_completed ? "completed" : "",
			proc->is_in_bg? "bg" : "fg"
	);
}


void clear_process(Process *proc)
{
	DEBUG_START("Clearing the process ...");

	free(proc->name);
	free(proc->next);

	proc->name = NULL;
	proc->next = NULL;
	proc->pid = 0;
	proc->pgid = 0;
	proc->in_fileno = STDIN_FILENO;
	proc->out_fileno = STDOUT_FILENO;
	proc->err_fileno = STDERR_FILENO;
	proc->is_stopped = 0;
	proc->is_completed = 0;
	proc->is_in_bg = 0;
	proc->status = 0;

	DEBUG_END("done.");
}


void delete_process(Process *proc)
{
	DEBUG_START("Deleting the process ...");

	clear_process(proc);
	free(proc);

	DEBUG_END("done.");
}


// ------------------- PROCESS GROUP ------------------- //

ProcessGroup *create_process_group(pid_t pgid)
{
	DEBUG_START("Creating the process group with pgid %d ...", pgid);

	ProcessGroup *group = (ProcessGroup*)malloc(sizeof(ProcessGroup));
	group->head = NULL;
	group->next_group = NULL;
	group->term_modes = &shell_term_modes;
	clear_process_group(group);

	group->pgid = pgid;

	DEBUG_END("done.");
	return group;
}


void push_process_in_group(Process *proc, ProcessGroup *group)
{
	if ((group == NULL)
			|| (proc == NULL))
		return;

	DEBUG_START("Pushing process with pid %d into group pgid %d ...", proc->pid, group->pgid);

	if (group->head == NULL)
	{
		group->head = proc;
		group->pgid = proc->pgid;

		DEBUG_END("done (pushed into head).");
		return;
	}

	Process *cursor;
	for (cursor = group->head; (cursor->next) != NULL; cursor = cursor->next);
	cursor->next = proc;
	proc->pgid = group->pgid;

	DEBUG_END("done (pushed after %d).", cursor->pid);
}


int remove_process_from_group(pid_t pid, ProcessGroup *group)
{
	if ((group == NULL)
			|| (group->head == NULL)
			|| (pid < 0))
		return 0;

	DEBUG_START("Removing process with pid %d from group pgid %d ...", pid, group->pgid);

	Process *cursor;
	if ((group->head)->pid == pid)
	{
		cursor = (group->head)->next;
		delete_process(group->head);
		group->head = cursor;

		DEBUG_END("done (removed from head).");
		return 1;
	}

	for (cursor = group->head; (cursor->next) != NULL; cursor = cursor->next)
	{
		if ((cursor->next)->pid == pid)
		{
			Process *next_proc = (cursor->next)->next;
			delete_process(cursor->next);
			cursor->next = next_proc;

			DEBUG_END("done (removed).");
			return 1;
		}
	}

	DEBUG_END("failed (not found).");
	return 0;
}


void show_process_group(ProcessGroup *group)
{
	if (group == NULL)
		return;

	DEBUG_START("Showing the process group %d ...", group->pgid);

	printf("Process group %d", group->pgid);
	Process *proc;
	for (proc = group->head; proc != NULL; proc = proc->next)
	{
		printf("\t");
		show_process(proc);
	}

	DEBUG_END("done.");
}


void clear_process_group(ProcessGroup *group)
{
	if (group == NULL)
		return;

	DEBUG_START("Clearing the process group with pgid %d", group->pgid);

	Process *cursor;
	Process *next_proc;
	for (cursor = group->head; cursor != NULL; cursor = next_proc)
	{
		next_proc = cursor->next;
		delete_process(cursor);
	}

	group->head = NULL;
	group->pgid = 0;

	DEBUG_END("done.");
}


void delete_process_group(ProcessGroup *group)
{
	if (group == NULL)
		return;

	DEBUG_START("Deleting the process group with pgid %d", group->pgid);

	clear_process_group(group);

	DEBUG_END("done.");
}


// ------------------- PROCESS LIST ------------------- //

ProcessList *create_process_list()
{
	DEBUG_START("Creating the process group ...");

	ProcessList *list = (ProcessList*)malloc(sizeof(ProcessList));
	list->first = NULL;

	clear_process_list(list);

	DEBUG_END("done.");
	return list;
}


Process *find_process_in_list(pid_t pid, ProcessList *list)
{
	if ((list == NULL)
			|| (pid < 0))
		return NULL;

	DEBUG_START("Searching the process in list with pid %d...", pid);

	ProcessGroup *group;
	Process *proc;
	for (group = list->first; group != NULL; group = group->next_group)
	{
		for (proc = group->head; proc != NULL; proc = proc->next)
		{
			if (proc->pid == pid)
			{
				DEBUG_END("done (found).");
				return proc;
			}
		}
	}

	DEBUG_END("failed (not found).");
	return NULL;
}


void push_process_into_list(Process *proc, ProcessList *list)
{
	if ((list == NULL)
			|| (proc == NULL)
			|| (proc->pgid < 0))
		return;

	DEBUG_START("Pushing the process with pid %d into into list with pgid %d ...", proc->pid, proc->pgid);

	if (list->first == NULL)
	{
		list->first = create_process_group(proc->pgid);
		push_process_in_group(proc, list->first);

		DEBUG_END("done (pushed into head).");
		return;
	}

	ProcessGroup *last_group;
	ProcessGroup *group;
	for (group = list->first; group != NULL; group = group->next_group)
	{
		if (group->pgid == proc->pgid)
		{
			push_process_in_group(proc, group);

			DEBUG_END("done (existing group was found).");
			return;
		}

		last_group = group;
	}

	last_group->next_group = create_process_group(proc->pgid);
	push_process_in_group(proc, last_group->next_group);

	DEBUG_END("done (pushed into new group).");
}


int remove_process_from_list(pid_t pid, ProcessList *list)
{
	if ((list == NULL)
			|| (pid < 0))
		return 0;

	DEBUG_START("Removing the process from list with pid %d...", pid);

	ProcessGroup *group;
	for (group = list->first; group != NULL; group = group->next_group)
	{
		if (remove_process_from_group(pid, group))
		{
			DEBUG_END("done.");
			return 1;
		}
	}

	DEBUG_END("failed (not found).");
	return 0;
}


ProcessGroup *find_process_group_in_list(pid_t pgid, ProcessList *list)
{
	if ((list == NULL)
			|| (pgid < 0))
		return NULL;

	DEBUG_START("Searching the process in list with pgid %d...", pgid);

	ProcessGroup *group;
	for (group = list->first; group != NULL; group = group->next_group)
	{
		if (group->pgid == pgid)
		{
			DEBUG_END("done (found).");
			return group;
		}
	}

	DEBUG_END("failed (not found).");
	return NULL;
}


void push_process_group_into_list(ProcessGroup *group, ProcessList *list)
{
	if ((list == NULL)
			|| (group == NULL))
		return;

	DEBUG_START("Pushing the process group with pgid %d into into list ...", group->pgid);

	if (list->first == NULL)
	{
		list->first = group;

		DEBUG_END("done (pushed into head).");
		return;
	}

	ProcessGroup *cursor;
	for (cursor = list->first; (cursor->next_group) != NULL; cursor = cursor->next_group);

	(cursor->next_group) = group;

	DEBUG_END("done (as new group).");
}


int remove_process_group_from_list(pid_t pgid, ProcessList *list)
{
	if ((list == NULL)
			|| (list->first == NULL)
			|| (pgid < 0))
		return 0;

	DEBUG_START("Removing the process group with pgid %d from list ...", pgid);

	ProcessGroup *group;
	if ((list->first)->pgid == pgid)
	{
		group = (list->first)->next_group;
		delete_process_group(list->first);
		list->first = group;

		DEBUG_END("done (head removed).");
		return 1;
	}

	ProcessGroup *last_group;
	for (group = list->first; group != NULL; group = group->next_group)
	{
		if (group->pgid == pgid)
		{
			last_group->next_group = group->next_group;
			delete_process_group(group);

			DEBUG_END("done (group found).");
			return 1;
		}

		last_group = group;
	}

	DEBUG_END("failed (group not found).");
	return 0;
}


void show_process_list(ProcessList *list)
{
	if (list == NULL)
		return;

	DEBUG_START("Showing the process list ...");

	ProcessGroup *group;
	for (group = list->first; group != NULL; group = group->next_group)
		show_process_group(group);

	DEBUG_END("done.");
}


void clear_process_list(ProcessList *list)
{
	if (list == NULL)
		return;

	DEBUG_START("Clearing the process list ...");
	
	ProcessGroup *group;
	ProcessGroup *next_group;
	for (group = list->first; group != NULL; group = next_group)
	{
		DEBUG_SAY("Removing group [%d]\n", group->pgid);
		next_group = group->next_group;
		delete_process_group(group);
	}

	list->first = NULL;

	DEBUG_END("done.");
}


void delete_process_list(ProcessList *list)
{
	if (list == NULL)
		return;

	DEBUG_START("Deleting the process list ...");

	clear_process_list(list);
	free(list);

	DEBUG_END("done.");
}


// ------------------- EXTRA FUNCTIONS ------------------- //

int was_process_group_stopped(ProcessGroup *group)
{
	DEBUG_START("Check for process group was stopped ...");
	Process *proc;

	for (proc = group->head; proc != NULL; proc = proc->next)
	{
		if (!(proc->is_completed)
				&& !(proc->is_stopped))
		{
			DEBUG_END("done (running process with pid %d was found)", proc->pid);
			return 0;
		}
	}

	DEBUG_END("done (running process was not found).");
	return 1;
}


int was_process_group_completed(ProcessGroup *group)
{
	DEBUG_START("Check for process group was completed ...");
	Process *proc;

	for (proc = group->head; proc != NULL; proc = proc->next)
	{
		if (!(proc->is_completed))
		{
			DEBUG_END("done (not completed process with pid %d was found)", proc->pid);
			return 0;
		}
	}

	DEBUG_END("done (completed process was not found).");
	return 1;
}
