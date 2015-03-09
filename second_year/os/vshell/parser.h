#ifndef __PARSER_H__
#define __PARSER_H__


typedef struct CommandArguments
{
	char *ins;
	char *outs;
	char *appends;
	char *origin;
	int is_in_background;
	int is_valid;
	StringArray *args;
} CmdArguments;


StringArray *split(char *line);
CmdArguments *get_empty_command_call(char *cmd_name);
CmdArguments *get_command_call(char *line);
void show_command_call(CmdArguments *cmd_call, FILE *stream);
void clear_command_call(CmdArguments *cmd_call);
int do_cmd(CmdArguments *call, CmdArray *cmds);


// __PARSER_H__
#endif
