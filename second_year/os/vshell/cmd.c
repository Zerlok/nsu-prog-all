#include "main.h"
#include "cmd.h"


void CMD_exit()
{
	printf("Exiting the shell...\n");
}


Cmd *create_cmd(char *name, void (*func)(void))
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


Commands *get_commands(int length)
{
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
	check_length_and_expand_commands(cmds);
	
	cmds->used_length++;
	
	cmds->data[cmds->used_length] = create_cmd(cmd_name, function);
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

		printf("\b\b");
	}

	printf("] (%ld, %ld)\n", cmds->used_length, cmds->allocated_length);
}
