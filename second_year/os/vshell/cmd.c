#include "main.h"

#include "array.h"
#include "cmd.h"


CmdDeclaration *create_cmd(
		char *name,
		int ((*func)(FILE*, FILE*, StringArray*)))
{
	if ((name == NULL)
		|| (func == NULL))
		return NULL;

	if (DEBUG)
		printf("\nCreating the %s command ...\n", name);

	CmdDeclaration *command = (CmdDeclaration*)malloc(sizeof(CmdDeclaration));

	if (DEBUG)
		printf("\t memory space was allocated\n");

	command->name = (char*)calloc(sizeof(char), strlen(name) + 1);
	strcpy(command->name, name);

	if (DEBUG)
		printf("\t %s name was copied\n", name);

	command->func = func;

	if (DEBUG)
		printf("\t %s function was assigned\n", name);
	
	if (DEBUG)
		printf("Done.\n");

	return command;
}


CmdArray *get_commands_array(int length)
{
	if (length < 1)
		length = 1;

	if (DEBUG)
		printf("\nCreating the array of commands ... ");

	CmdArray *cmds = (CmdArray*)malloc(sizeof(CmdArray));

	cmds->data = (CmdDeclaration**)calloc(sizeof(CmdDeclaration*), length);
	cmds->allocated_length = length;
	cmds->used_length = 0;

	if (DEBUG)
		printf("done.\n");

	return cmds;
}


void check_length_and_expand_commands_array(CmdArray *cmds)
{
	if ((cmds->allocated_length)
		!= (cmds->used_length))
		return;
	
	cmds->allocated_length *= CMD_ARRAY_EXPANDING_CRITERIA;
	cmds->data = (CmdDeclaration**)realloc(cmds->data, cmds->allocated_length);
}


void push_into_commands_array(
		char *cmd_name,
		int ((*function)(FILE*, FILE*, StringArray*)),
		CmdArray *cmds)
{
	if ((cmd_name == NULL)
		|| (function == NULL))
	{
		printf("Invalid command while pushing it into commands array!\n");
		return;
	}

	if (cmds == NULL)
	{
		printf("Invalid commands array while pushing new command into it!\n");
		return;
	}

	if (DEBUG)
		printf("\nPushing the command into commands array ... ");

	check_length_and_expand_commands_array(cmds);

	cmds->data[cmds->used_length] = create_cmd(cmd_name, function);
	cmds->used_length++;

	if (DEBUG)
		printf("done.\n");
}


void show_commands_array(CmdArray *cmds, FILE *stream)
{
	if (cmds == NULL)
		return;
	
	size_t i;

	fprintf(stream, "[");

	if (cmds->used_length != 0)
	{
		for (i = 0; i < cmds->used_length; i++)
		{
			fprintf(stream, "(%s : %p) ", (cmds->data[i])->name, (cmds->data[i])->func);
		}

		fprintf(stream, "\b");
	}

	fprintf(stream, "] (%ld, %ld)\n", cmds->used_length, cmds->allocated_length);

	if (DEBUG)
		printf("done.\n");
}


void clear_commands_array(CmdArray *cmds)
{
	if (cmds == NULL)
		return;

	if (DEBUG)
		printf("\nClearing the commands array ... ");

	size_t i;

	for (i = 0; i < cmds->used_length; i++)
		free((cmds->data[i])->name);

	cmds->used_length = 0;

	if (DEBUG)
		printf("done.\n");
}


void delete_commands_array(CmdArray *cmds)
{
	if (cmds == NULL)
		return;

	if (DEBUG)
		printf("Deleting the commands array ... ");

	clear_commands_array(cmds);

	free(cmds->data);

	if (DEBUG)
		printf("done.\n");
}