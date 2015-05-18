#ifndef __VSHELL_H__
#define __VSHELL_H__


// typedef void (*sighandler_t)(int);


typedef struct Vshell
{
	ProcessArray *processes;
	StringArray *history;
} SHELL;


void handle_signal(int signum);

void VSHELL_INIT(int argc, char **argv, SHELL *shell);
void VSHELL_RUN(SHELL *shell);
void VSHELL_CLOSE(SHELL *shell);


// __VSHELL_H__
#endif
