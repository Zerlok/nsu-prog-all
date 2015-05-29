#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/procset.h>
#include <unistd.h>


#define TIMEOUT 10


static int pid;


void wait_terminal_input()
{
	signal(SIGTTIN, SIG_IGN);

}


void sigalarm(int sig)
{
	sigsend(P_PID, pid, SIGQUIT);
}


int main(int argc, char **argv)
{
void sigalarm(int);
	int status;
	pid = fork();
	
	if (pid == 0)
	{
		wait_terminal_input();
		perror(argv[1]);
		exit(127);
	}

	signal(SIGALRM, sigalarm);
	alarm(TIMEOUT);

	while (wait(&status) == -1)
	{
		if (errno == EINTR)
		{
		errno = 0;
		printf("%s: timed out\n", argv[1]);
		}
		else
		{
			perror(argv[0]);
			break;
		}
	}

	exit(WEXITSTATUS(status));
}
