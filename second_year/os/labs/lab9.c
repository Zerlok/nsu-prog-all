#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <wait.h>


int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s [bin]\n", argv[0]);
		return 1;
	}

	pid_t pid, ret;

	id = fork(); // forking...
	if (id < 0)
	{
		perror(strerror(errno));
		return 1;
	}
	else if (id == 0)
	{
		char *args = argv+1;
		execvp(args[0], args);
		perror(strerror(errno));
		return 1;
	}

	printf("parent: waiting for child: %ld\n", id);

	pid = waitpid(id, NULL, 0);
	if (pid >= 0)
	{
		printf("\n  parent: waiting for child: %ld \n", pid);
	}
	else
	{
		perror(strerror(errno));
	}

	printf("child's status: %d\n", WEXITSTATUS(status));
	return 0;
}