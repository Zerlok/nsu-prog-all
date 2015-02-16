#ifndef __VSHELL_H__
#define __VSHELL_H__


typedef struct Vshell
{
	char *username;
	StringArray *history;
	Commands *cmds;
} SHELL;


void VSHELL_init(int argc, char **argv, SHELL *shell);
void VSHELL_run(SHELL *shell);
void VSHELL_close(SHELL *shell);


// __VSHELL_H__
#endif
