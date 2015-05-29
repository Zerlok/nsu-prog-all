#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>


int main(int argc, char **argv)
{
	pid_t id, pid;
	int status;

	id = fork(); // forking...
	if (id < 0)
	{
		perror("couldn't create a child process.");
		return 1;
	}
	else if (id == 0)
	{
		execlp("cat", "cat", "/home/zerlok/Downloads/netprint.ppd", (char*)NULL);
		perror(argv[0]);
		return 1;
	}

	printf("parent: waiting for child: %d\n", id);

	pid = waitpid(id, NULL, 0);
	if (pid >= 0)
	{
		printf("parent: waiting for child: %d \n", pid);
	}
	else
	{
		perror("waitpid error.");
	}

	printf("child's status: %d\n", WEXITSTATUS(status));
	return 0;
}
