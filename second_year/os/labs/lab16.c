#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>


#define TIMEOUT 5


void wait_terminal_input()
{
	int fd;
	char ch;
	struct termios tty, savtty;

	fd = open("/dev/tty", O_RDONLY);
	tcgetattr(fd, &tty);

	if (isatty(fileno(stdout)) == 0)
	{
		fprintf(stderr, "stdout not terminal\n");
		exit(1);
	}

	savtty = tty;
	tty.c_lflag &= ~(ISIG | ICANON | ECHO);
	tty.c_cc[VTIME] = 0;
	tty.c_cc[VMIN] = 0;
	
	tcsetattr(fd, TCSAFLUSH, &tty);
	setbuf(stdout, (char *)NULL);
	
	printf("Are you OK? (y/n): ");
	while ((ch != 'y') && (ch != 'n'))
		read(fd, &ch, 1);

	if (ch == 'y')
		printf("\nMe too ^__^\n");

	else
		printf("\nOh :(\n");

	tcsetattr(fd, TCSAFLUSH, &savtty);
}


int main(int argc, char **argv)
{
	alarm(TIMEOUT);
	wait_terminal_input();
}
