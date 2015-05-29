#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>


#define   MAXTRIES   5


int main(int argc, char **argv)
{
	int try = 0;
	int fd = open("file.txt", O_RDONLY);
	struct flock lock;

	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0; /* whole file address space */

	while (fcntl(fd, F_SETLK, &lock) == -1)
	{
		if ((errno == EACCES) || (errno == EAGAIN))
		{
			++try;
			if (try <= MAXTRIES)
			{
				sleep(1);
				continue;
			}

			printf("%s busy -- try later\n",
					argv[1]);
		
			exit(2);
		}

		perror(argv[1]);
		exit(3);
	}

	system("nano");

	lock.l_type = F_UNLCK;    /* unlock file */
	fcntl(fd, F_SETLK, &lock);
	close(fd);	return 0;
}
