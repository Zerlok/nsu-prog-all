#include "main.h"

#include "debug.h"
#include "array.h"
#include "cmd.h"


CmdDeclaration *create_cmd(
		char *name,
		char *filename)
{
	if ((name == NULL)
		|| (filename == NULL))
		return NULL;

	DEBUG_START("Creating the %s command ...", name);

	CmdDeclaration *command = (CmdDeclaration*)malloc(sizeof(CmdDeclaration));

	DEBUG_SAY("memory space was allocated\n");

	command->name = (char*)calloc(sizeof(char), strlen(name) + 1);
	strcpy(command->name, name);

	DEBUG_SAY("%s name was copied\n", name);

	command->filename = (char*)calloc(sizeof(char), strlen(filename) + 1);
	strcpy(command->filename, filename);

	DEBUG_SAY("%s function was assigned\n", name);
	
	DEBUG_END("done.");
	return command;
}


CmdArray *get_commands_array(int length)
{
	if (length < 1)
		length = 1;

	DEBUG_START("Creating the array of commands ...");

	CmdArray *cmds = (CmdArray*)malloc(sizeof(CmdArray));

	cmds->data = (CmdDeclaration**)calloc(sizeof(CmdDeclaration*), length);
	cmds->used_length = 0;
	cmds->allocated_length = length;

	DEBUG_END("done.");

	return cmds;
}


void check_length_and_expand_commands_array(CmdArray *cmds)
{
	if ((cmds->allocated_length)
		!= (cmds->used_length))
		return;

	if (cmds->allocated_length == 0)
		cmds->allocated_length = 1;
	
	else	
		cmds->allocated_length *= CMD_ARRAY_EXPANDING_CRITERIA;
	
	cmds->data = (CmdDeclaration**)realloc(cmds->data, cmds->allocated_length);
}


void push_into_commands_array(
		char *cmd_name,
		char *filename,
		CmdArray *cmds)
{
	if ((cmd_name == NULL)
		|| (filename == NULL))
	{
		printf("Invalid command while pushing it into commands array!\n");
		return;
	}

	if (cmds == NULL)
	{
		printf("Invalid commands array while pushing new command into it!\n");
		return;
	}

	DEBUG_START("Pushing the command into commands array ...");

	check_length_and_expand_commands_array(cmds);

	cmds->data[cmds->used_length] = create_cmd(cmd_name, filename);
	cmds->used_length++;

	DEBUG_END("done.");
}


void show_commands_array(CmdArray *cmds, FILE *stream)
{
	if (cmds == NULL)
		return;

	DEBUG_START("Showing the commands array ...");

	size_t i;

	fprintf(stream, "[");

	if (cmds->used_length != 0)
	{
		for (i = 0; i < cmds->used_length; i++)
		{
			fprintf(stream, "(%s : %s) ", (cmds->data[i])->name, (cmds->data[i])->filename);
		}

		fprintf(stream, "\b");
	}

	fprintf(stream, "] (%ld, %ld)\n", cmds->used_length, cmds->allocated_length);

	DEBUG_END("done.");
}


void clear_commands_array(CmdArray *cmds)
{
	if (cmds == NULL)
		return;

	DEBUG_START("Clearing the commands array ...");

	size_t i;

	for (i = 0; i < cmds->used_length; i++)
	{
		DEBUG_SAY("%ld : Removing %s - %s\n", i, (cmds->data[i])->name, (cmds->data[i])->filename);
		free((cmds->data[i])->name);
		free((cmds->data[i])->filename);
	}

	cmds->used_length = 0;
	
	DEBUG_END("done.");
}


void delete_commands_array(CmdArray *cmds)
{
	if (cmds == NULL)
		return;

	DEBUG_START("Deleting the commands array ...");

	clear_commands_array(cmds);

	free(cmds->data);
	free(cmds);

	DEBUG_END("done.");
}


int do_cmd(CmdArguments *call, CmdArray *cmds)
{
	if ((call == NULL)
		|| (call->origin == NULL))
		return CODE_WAIT;

	if (!(call->is_valid))
		return CODE_INVALID_CALL;

	DEBUG_START("Calling the %s command ...", call->origin);
	int i;
	pid_t pid;

	if (!strcmp(call->origin, CMD_EXIT))
	{
		DEBUG_END("done (exit).");
		return CODE_EXIT;
	}

	if (!strcmp(call->origin, CMD_HELP))
	{
		for (i = 0; i < cmds->used_length; i++)
			printf("%s - %s\n", (cmds->data[i])->name, (cmds->data[i])->filename);

		DEBUG_END("done (help).");
		return CODE_SUCCESS;
	}

	for (i = 0; i < cmds->used_length; i++)
	{
		if (!strcmp(call->origin, (cmds->data[i])->name))
		{
			int status;
			
			DEBUG_SAY("Forking '%s' == '%s' ...\n", call->origin, (cmds->data[i])->name);
			
			pid = fork();

			if (pid < 0) // Do it if fork failed.
			{
				printf("Cannot create a fork.\n");
				DEBUG_END("done (failed fork).");
				return CODE_FAIL;
			}
			else if (pid > 0) // Do it in parent process.
			{
				DEBUG_SAY("Parent pid: %d\n", pid);
				waitpid(pid, &status, 0);
			}
			else // Do it in child process.
			{
				DEBUG_SAY("Calling '%s' with arguments: ", (cmds->data[i])->filename);
				if (DEBUG)
				{
					int arg_index;
					for (arg_index = 0; arg_index < call->argc; arg_index++) printf("%s ", call->argv[arg_index]);
					printf("\n");
				}

				// if (call->ins != NULL)
				// {
				// 	int stream_in = open(call->ins, "r");
					
				// 	if (stream_in != -1)
				// 		dup2(stream_in, 0);

				// 	else
				// 		perror(strerror(errno));
				// }

				// if (call->outs != NULL)
				// {
				// 	int stream_out = open(call->outs, "w");
					
				// 	if (stream_out != -1)
				// 	{
				// 		close(stdout);
				// 		dup(stream_out);
				// 	}

				// 	else
				// 		perror(strerror(errno));
				// }

				// else if (call->appends != NULL)
				// {
				// 	int stream_out = open(call->appends, "r+");
					
				// 	if (stream_out != -1)
				// 		dup2(stream_out, 1);

				// 	else
				// 		perror(strerror(errno));
				// }

				status = execvp((cmds->data[i])->filename, call->argv);
				
				if (status == -1)
				{
					perror(strerror(errno));

					DEBUG_END("done (failed exec).");
					return CODE_FAIL;
				}
			} // ENDIF

			DEBUG_END("done (successed fork).");
			return CODE_SUCCESS;
		} // ENDIF (!strcmp)
	} // ENDFOR (cmds.used_length)

	DEBUG_END("done (command not found).");
	return CODE_UNKNOWN_CMD;
}
