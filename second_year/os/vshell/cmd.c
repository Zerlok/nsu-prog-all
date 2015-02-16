#include "main.h"
#include "cmd.h"


void CMD_exit()
{
	printf("Exiting the shell...\n");
}


Cmd *create_cmd(char *name, void (*func)(void))
{
	if ((name != NULL)
		&& (func != NULL))
	{
		printf("Creating the %s command...\n", name);

		Cmd *command = (Cmd*)malloc(sizeof(Cmd));

		printf("\t memory was allocated\n");

		command->name = (char*)calloc(sizeof(char), strlen(name));
		strcpy(command->name, name);

		printf("\t %s name was copied\n", name);

		command->func = func;

		printf("\t %s function was declared\n", name);

		return command;
	}
	else
	{
		return NULL;
	}
}


Commands *get_commands(int length)
{
	if (length < 1)
		length = 1;

	printf("Creating the array of commands...\n");

	Commands *cmds = (Commands*)malloc(sizeof(Commands));

	cmds->data = (Cmd**)calloc(sizeof(Cmd*), length);
	cmds->data[0] = create_cmd("exit", CMD_exit);

	cmds->allocated_length = length;
	cmds->used_length = 1;

	return cmds;
}


void check_length_and_expand_commands(Commands *cmds)
{
	if ((cmds->allocated_length)
		== (cmds->used_length))
	{
		cmds->allocated_length *= CMD_EXPANDING_CRITERIA;
		cmds->data = (Cmd**)realloc(cmds->data, cmds->allocated_length);
	}
}


void push_into_commands(char *cmd_name, void (*function)(void), Commands *cmds)
{
	if ((cmd_name != NULL)
		&& (function != NULL))
	{
		check_length_and_expand_commands(cmds);
		
		cmds->data[cmds->used_length] = create_cmd(cmd_name, function);
		
		cmds->used_length++;
	}
}


void show_commands(Commands *cmds)
{
	size_t i;

	printf("[");

	if (cmds->used_length != 0)
	{
		for (i = 0; i < cmds->used_length; i++)
		{
			printf("(%s : %p) ", (cmds->data[i])->name, (cmds->data[i])->func);
		}

		printf("\b");
	}

	printf("] (%ld, %ld)\n", cmds->used_length, cmds->allocated_length);
}


void clear_commands(Commands *cmds)
{
	size_t i;

	for (i = 0; i < cmds->used_length; i++)
		free((cmds->data[i])->name);

	cmds->used_length = 0;
}


void delete_commands(Commands *cmds)
{
	clear_commands(cmds);

	free(cmds->data);
}