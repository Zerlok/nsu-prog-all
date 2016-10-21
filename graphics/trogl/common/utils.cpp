#include "utils.h"


#include <sys/time.h>


static struct timeval timestamp;


double getTimeDouble()
{
	gettimeofday(&timestamp, NULL);
	return ((timestamp.tv_sec % 10000) * 10) + (timestamp.tv_usec / 10000) / 10.0;
}


size_t getTimestamp()
{
	gettimeofday(&timestamp, NULL);
	return timestamp.tv_sec;
}
