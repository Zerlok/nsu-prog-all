#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char **argv)
{
	int try = 0;
	int fd = open("file.txt", O_RDONLY);

	if (flock(fd, LOCK_EX | LOCK_NB) < 0)
	{
		perror("flock");
		exit(1);
	}

	// system("nano file.txt");
	while (1);

	flock(fd, LOCK_UN);
	close(fd);
	return 0;
}
