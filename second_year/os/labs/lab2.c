#define _GNU_SOURCE /* for tm_gmtoff and tm_zone */


#include <stdio.h>
#include <time.h>


int main(int argc, char **argv, char **env)
{
	putenv("TZ=America/Los_Angeles");

	time_t t = time(NULL);
	struct tm local_time;

	localtime_r(&t, &local_time);
	printf("Current time in timezone '%s' is %02d:%02d:%02d.\n",
		   local_time.tm_zone,
		   local_time.tm_hour,
		   local_time.tm_min,
		   local_time.tm_sec
	);

	return 0;
}
