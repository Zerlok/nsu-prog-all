#include "utils.hpp"


#include <sys/time.h>
#include <sstream>
#include <iostream>


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


std::string path::basename(const std::string& path)
{
	const size_t pos = path.rfind('/') + 1;
	const std::string base = path.substr(pos, path.length() - pos);
	return base;
}


std::string path::clearname(const std::string& path)
{
	const std::string filename = basename(path);
	const size_t pos = filename.rfind('.');
	const std::string cl = filename.substr(0, pos);
	return cl;
}


std::string path::dirname(const std::string& path)
{
	const size_t pos = path.rfind('/');
	const std::string dir = path.substr(0, pos);
	return dir;
}


std::string path::join(const std::string& path1, const std::string& path2)
{
	std::stringstream ss;
	ss << path1 << '/' << path2;
	return ss.str();
}
