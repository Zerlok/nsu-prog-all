#ifndef __CMD_H__
#define __CMD_H__


#define DEBUG_SHOW_CMD(command)(\
{\
	if (DEBUG)\
	{\
		printf("Cmd structure\n");\
		printf(" * Origin      : %s\n", command->origin);\
		printf(" * Ins         : %s\n", command->ins);\
		printf(" * Outs        : %s\n", command->outs);\
		printf(" * Appends     : %s\n", command->appends);\
		printf(" * Pipe        : %p\n", command->pipe);\
		printf(" * In back     : %s\n", command->is_in_background ? "True" : "False");\
		printf(" * Valid       : %s\n", command->is_valid ? "True" : "False");\
		printf(" * ArgC        : %d\n", command->argc);\
		printf(" * ArgV (last) : %s\n", command->argv[command->argc - 1]);\
	}\
})


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
