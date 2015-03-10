#ifndef __VSHELL_H__
#define __VSHELL_H__


typedef void (*sighandler_t)(int);


typedef struct Vshell
{
	char *username;
	StringArray *history;
	CmdArray *cmds;
} SHELL;


void handle_signal(int signum);

void VSHELL_init(
		int argc,
		char **argv,
		SHELL *shell);

int VSHELL_add_command(
		SHELL *shell,
		char *command_name,
		int ((*function)(FILE*, FILE*, StringArray*)));
		// int ((*function)(...)));

void VSHELL_run(SHELL *shell);

void VSHELL_close(SHELL *shell);


// __VSHELL_H__
#endif
