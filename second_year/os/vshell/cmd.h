#ifndef __CMD_H__
#define __CMD_H__


typedef struct CommandCall
{
	char *ins;
	char *outs;
	char *appends;
	char *origin;
	int is_in_background;
	int is_valid;
	int argc;
	char **argv;
} Cmd;


int redirect_stream(int old_stream, char *filename, int flags);
int run_command(Cmd *call, ProcessArray *processes);
void run_child(pid_t parentid, Cmd *command);

Cmd *get_empty_command(char *cmd_name);
Cmd *build_command(char *line);
void show_command(Cmd *command, FILE *stream);
void clear_command(Cmd *command);
void delete_command(Cmd *command);


// __CMD_H__
#endif
