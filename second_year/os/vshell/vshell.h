#ifndef __VSHELL_H__
#define __VSHELL_H__


typedef struct ShellStructure
{
	pid_t pgid;
	int input_fileno;
	int is_interactive;
	struct termios *term_modes;
	ProcessList *processes;
} Shell;

void SHELL_INIT(int argc, char **argv, Shell *shell);
void SHELL_RUN(Shell *shell);
void SHELL_CLOSE(Shell *shell);


void put_process_in_foreground(ProcessGroup *group, int cont, Shell *shell);
void put_process_in_background(ProcessGroup *group, int cont);
int set_process_status(pid_t pid, int status, ProcessList *processes);
void update_processes(ProcessList *processes);
void wait_for_process_group(ProcessGroup *group, ProcessList *processes);
void update_processes_status(ProcessList *processes);


// __VSHELL_H__
#endif
