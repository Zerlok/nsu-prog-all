#ifndef __CMD_H__
#define __CMD_H__


typedef struct CommandDeclaration
{
	char *name;
	char *filename;
} CmdDeclaration;


typedef struct CommandArray
{
	size_t allocated_length;
	size_t used_length;
	CmdDeclaration **data;
} CmdArray;


typedef struct CommandArguments
{
	char *ins;
	char *outs;
	char *appends;
	char *origin;
	int is_in_background;
	int is_valid;
	int argc;
	char **argv;
} CmdArguments;


CmdDeclaration *create_cmd(
		char *name,
		char *filename);

CmdArray *get_commands_array(int length);
void check_length_and_expand_commands_array(CmdArray *cmds);
void push_into_commands_array(
		char *cmd_name,
		char *filename,
		CmdArray *cmds);

void show_commands_array(CmdArray *cmds, FILE *stream);
void clear_commands_array(CmdArray *cmds);
void delete_commands_array(CmdArray *cmds);


int do_cmd(CmdArguments *call, CmdArray *cmds);


// __CMD_H__
#endif