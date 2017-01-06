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


std::string path::extension(const std::string& path)
{
	const size_t pos = path.rfind('.') + 1;
	const std::string ext = path.substr(pos, path.length() - pos);
	return ext;
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


bool stringutils::startswith(const std::string& str, const std::string& substr)
{
	if (str.size() < substr.size())
		return false;

	for (size_t i = 0; i < substr.size(); ++i)
		if (str[i] != substr[i])
			return false;

	return true;
}


bool stringutils::contains(const std::string& str, const std::string& substr)
{
	return (find(str, substr) != std::string::npos);
}


size_t stringutils::find(const std::string& str, const std::string& substr)
{
	const size_t len = str.size();
	const size_t subLen = substr.size();
	size_t i = 0;
	size_t j = 0;

	for (i = 0; i < (len - subLen); i += j + 1)
	{
		j = 0;
		while ((j < subLen)
			   && (str[i+j] == substr[j]))
			++j;

		if (j == subLen)
			return i;
	}

	return std::string::npos;
}
