#ifndef UTILS_H
#define UTILS_H


#include <sys/time.h>


double getTime()
{
	static struct timeval tp;
	gettimeofday(&tp, NULL);
	return ((tp.tv_sec % 10000) * 10) + (tp.tv_usec / 10000) / 10.0;
}


#endif // UTILS_H
