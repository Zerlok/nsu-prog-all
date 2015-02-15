#include "main.h"
#include "cmd.h"


Commands *get_commands(int length)
{
	Commands *cmds = (Commands*)malloc(sizeof(Commands));

	cmds->name = (char**)calloc(sizeof(char*), length);
	// cmds->func = (void**)calloc(sizeof(void*), length);
	cmds->func = calloc(sizeof(void(*)(void)), length);
	cmds->allocated_length = length;
	cmds->used_length = 0;

	return cmds;
}


void check_length_and_expand_commands(Commands *cmds)
{
	if ((cmds->allocated_length)
		== (cmds->used_length))
	{
		cmds->allocated_length *= CMD_EXPANDING_CRITERIA;
		cmds->name = (char**)realloc(cmds->name, cmds->allocated_length);
		cmds->func = (void**)realloc(cmds->func, cmds->allocated_length);
	}
}


void push_into_commands(char *cmd_name, void *function, Commands *cmds)
{
	check_length_and_expand_commands(cmds);
	
	(cmds->name)[cmds->used_length + 1] = cmd_name;
	(cmds->func)[cmds->used_length + 1] = function;

	cmds->used_length++;
}


void show_commands(Commands *cmds)
{
	size_t i;

	printf("[");

	if (cmds->used_length != 0)
	{
		for (i = 0; i < cmds->used_length; i++)
		{
			printf("(%s : %p) ", cmds->name[i], cmds->func[i]);
		}

		printf("\b\b");
	}

	printf("] (%ld, %ld)\n", cmds->used_length, cmds->allocated_length);
}
