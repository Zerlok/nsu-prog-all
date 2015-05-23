#ifndef __CMD_H__
#define __CMD_H__


typedef struct Command
{
	char *origin;			// main command
	char *ins;				// input filename
	char *outs;				// output filename
	char *appends;			// append filename

	struct Command *pipe;	// pipe to next command

	int is_in_background;	// run it in background
	int is_valid;			// was call valid

	int argc;				// arguments num
	char **argv;			// arguments chars
} Cmd;


void run_child(pid_t parentid, Cmd *command);
int run_command(Cmd *call, ProcessArray *processes);
int redirect_stream(int old_stream, char *filename, int flags);

Cmd *create_empty_command(char *cmd_name);
Cmd *build_command(char *line);
void show_command(Cmd *command, FILE *stream);
void clear_command(Cmd *command);
void delete_command(Cmd *command);


// __CMD_H__
#endif
