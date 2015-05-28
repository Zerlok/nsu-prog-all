#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>


int main(int argc, char **argv)
{
	FILE *fp;				// real - who create process(same as UID). Usage:for control system resourses 
	uid_t uid;				// effective - who run this process, if this information change. Usage: for determine permessions

	if (argc < 2)
	{
		fprintf(stderr, "Usage: program name  %s [filename]\n", argv[0]);
		exit(1);
	}

	printf("First: uid=%ld and euid=%ld\n", getuid(), geteuid());

	if ((fp = fopen(argv[1], "r")) == NULL) 
	{
		perror(strerror(errno));
		perror(argv[0]);
		exit(2);
	}
	else 
	{
		printf("First open success\n");
		fclose(fp);
	}

	uid = getuid();
	setuid(uid);

	printf("Second: setuid(%ld):\n   uid=%ld, euid=%ld\n",
			uid,
			getuid(),
			geteuid()
	);

	if ((fp = fopen(argv[1], "r")) == NULL)
	{
		perror(strerror(errno));
		// perror(argv[0]);
		exit(3);
	}
	else
	{
		printf("Second open success\n");
		fclose(fp);
	}
}