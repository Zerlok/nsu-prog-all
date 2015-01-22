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
	
	for (auto it = v.begin();
		it != v.end();
		it++)
		out << (*it) << " ";

	out << "\b]\n";
}


// __MAIN_H__
#endif