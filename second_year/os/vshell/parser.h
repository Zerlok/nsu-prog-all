#ifndef __PARSER_H__
#define __PARSER_H__


StringArray *split(char *line);
CmdArguments *get_empty_command_call(char *cmd_name);
CmdArguments *get_command_call(char *line);
void show_command_call(CmdArguments *cmd_call, FILE *stream);
void clear_command_call(CmdArguments *cmd_call);


// __PARSER_H__
#endif
