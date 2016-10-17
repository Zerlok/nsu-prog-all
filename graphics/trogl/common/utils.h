#ifndef UTILS_H
#define UTILS_H


#include <sys/time.h>


static struct timeval TIMEVALUE;


static double getTimeDouble()
{
	gettimeofday(&TIMEVALUE, NULL);
	return ((TIMEVALUE.tv_sec % 10000) * 10) + (TIMEVALUE.tv_usec / 10000) / 10.0;
}


static size_t getTimeUInt()
{
	gettimeofday(&TIMEVALUE, NULL);
	return TIMEVALUE.tv_usec / 100000;
}


#endif // UTILS_H
