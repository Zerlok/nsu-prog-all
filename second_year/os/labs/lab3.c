#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: program name  %s [filename]\n", argv[0]);
		return 1;
	}

	FILE *fp;		// real - who create process(same as UID). Usage: control system resourses 
	uid_t uid;		// effective - who run this process, if this information change. Usage: determine permessions
	printf("First: uid=%d and euid=%d\n", getuid(), geteuid());

	if ((fp = fopen(argv[1], "r")) == NULL) 
	{
		perror(argv[0]);
		return 2;
	}
	else 
	{
		printf("First open success\n");
		fclose(fp);
	}

	uid = getuid();
	setuid(uid);

	printf("Second: setuid(%d):\n   uid=%d, euid=%d\n",
			uid,
			getuid(),
			geteuid()
	);

	if ((fp = fopen(argv[1], "r")) == NULL)
	{
		perror(argv[0]);
		return 3;
	}
	else
	{
		printf("Second open success\n");
		fclose(fp);
	}
}
