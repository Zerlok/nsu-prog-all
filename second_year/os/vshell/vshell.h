#ifndef __VSHELL_H__
#define __VSHELL_H__


typedef struct Vshell
{
	pid_t pgid;
	int input_fileno;
	int is_interactive;
	ProcessArray *processes;
} Shell;

void SHELL_INIT(int argc, char **argv, Shell *shell);
void SHELL_RUN(Shell *shell);
void SHELL_CLOSE(Shell *shell);


// __VSHELL_H__
#endif
