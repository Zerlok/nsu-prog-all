#ifndef __CMD_H__
#define __CMD_H__


#define CMD_EXPANDING_CRITERIA 2


#define CMD_EXIT 1


typedef struct CommandArray
{
	size_t allocated_length;
	size_t used_length;
	char **name;
	void (**func)(void);
} Commands;


Commands *get_commands(int length);
void check_length_and_expand_commands(Commands *cmds);
void push_into_commands(char *cmd_name, void *function, Commands *cmds);
void show_commands(Commands *cmds);


// __CMD_H__
#endif