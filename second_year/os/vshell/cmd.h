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
} Call;


int do_cmd(Call *call);


// __CMD_H__
#endif