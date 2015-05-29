#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char **argv)
{
	char *text = "AbraCaDAbracadABRa#";
	int len = strlen(text);

	int my_pipe[2];
	pid_t cid_r, cid_w;

// pipes setup.
	if (pipe(my_pipe) == -1)
	{
		perror("pipe");
		exit(1);
	}

// WRITER
	cid_w = fork();
	if (cid_w == 0)
	{
		int i;

		dup2(my_pipe[1], STDOUT_FILENO);
		close(my_pipe[1]);

		for (i = 0; i < len; i++)
			write(my_pipe[1], &(text[i]), 1);
	}
	else if (cid_w < 0)
	{
		perror("write child");
		exit(1);
	}

// READER
	cid_r = fork();
	if (cid_w == 0)
	{
		char ch;
		int status;

		dup2(my_pipe[0], STDIN_FILENO);
		close(my_pipe[0]);

		do
		{
			read(my_pipe[0], &ch, 1);
			printf("%c ", toupper(ch));
		} while (ch != '#');
	}
	else if (cid_w < 0)
	{
		perror("read child");
		exit(1);
	}

	close(my_pipe[0]);
	close(my_pipe[1]);

	return 0;
}
