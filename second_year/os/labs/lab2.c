#define _GNU_SOURCE /* for tm_gmtoff and tm_zone */


#include <stdio.h>
#include <time.h>


int main(int argc, char **argv, char **env)
{
	putenv("TZ=America/Los_Angeles");

	time_t t = time(NULL);
	struct tm lt;

	localtime_r(&t, &lt);
	printf("Current time in timezone '%s' is %02d:%02d:%02d.\n",
		   lt.tm_zone,
		   lt.tm_hour,
		   lt.tm_min,
		   lt.tm_sec
	);


	return 0;
}
