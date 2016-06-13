#ifndef __UTILS_H__
#define __UTILS_H__


#include <vector>
#include <algorithm>


namespace utils
{
	template<class T>
	T select_n_max(std::vector<T>& vec, const typename std::vector<T>::size_type n)
	{
		if (n == 0)
			return 0.0;

		std::sort(vec.begin(), vec.end());
		return vec[vec.size() - n];
	}
}


// __UTILS_H__
#endif
