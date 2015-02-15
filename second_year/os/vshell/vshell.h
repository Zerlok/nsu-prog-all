#ifndef __VSHELL_H__
#define __VSHELL_H__


#define STD_DUMP_FILENAME "vshel.dump"


typedef struct Vshell
{
	char *username;
	History *history;
	Commands *cmds;
} SHELL;


// __VSHELL_H__
#endif
