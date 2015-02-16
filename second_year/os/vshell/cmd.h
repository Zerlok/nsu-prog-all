#ifndef __CMD_H__
#define __CMD_H__


typedef struct Command
{
	char *name;
	void (*func)(void);
} Cmd;


typedef struct CommandArray
{
	size_t allocated_length;
	size_t used_length;
	Cmd **data;
} Commands;


Commands *get_commands(int length);
void check_length_and_expand_commands(Commands *cmds);
void push_into_commands(char *cmd_name, void (*function)(void), Commands *cmds);
void show_commands(Commands *cmds);
void clear_commands(Commands *cmds);
void delete_commands(Commands *cmds);


// __CMD_H__
#endif