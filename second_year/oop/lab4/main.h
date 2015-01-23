#ifndef __MAIN_H__
#define __MAIN_H__


#include <iostream>
#include <memory>
#include <algorithm>
#include <iterator>


template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v)
{
	out << "[";

	if (v.empty())
		out << " ";
	
	for (auto it = v.begin();
		it != v.end();
		it++)
		out << (*it) << " ";

	out << "\b]";
}


// __MAIN_H__
#endif