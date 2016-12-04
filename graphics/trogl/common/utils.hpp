#ifndef __UTILS_HPP__
#define __UTILS_HPP__


#include <stddef.h>
#include <iostream>
#include <string>
#include <vector>


double getTimeDouble();
size_t getTimestamp();


namespace path
{
	std::string basename(const std::string& path);
	std::string extension(const std::string& path);
	std::string clearname(const std::string& path);
	std::string dirname(const std::string& path);
	std::string join(const std::string& path1, const std::string& path2);
}


template<class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& values)
{
	out << '{';

	for (const T& val : values)
		out << val << ", ";

	out << '}';
	return out;
}


#endif // __UTILS_HPP__
