#ifndef __EXTRA_UTILS_H__
#define __EXTRA_UTILS_H__


#include <iostream>
#include <vector>
#include <cmath>
#include <gtest/gtest.h>


template<class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec)
{
	const size_t len = vec.size();
	std::cout << '[' << len << "] {";
	for (const T& v : vec)
		std::cout << v << ", ";

	if (len > 0)
		std::cout << "\b\b";

	std::cout << '}' << std::endl;
	return out;
}


template<class T>
inline T roundk(const T& val, const size_t& k = 0)
{
	long long int m = std::pow(10, k);
	return std::round(val * m) / m;
}


template<class T>
size_t bisect(const std::vector<T>& vec, const T& val)
{
	for (size_t i = 0; i < vec.size(); ++i)
		if (val < vec[i])
			return i;

	return 0;
}


template<class T>
size_t insort(std::vector<T>& vec, const T& val)
{
	const size_t idx = bisect(vec, val);
	vec.insert(vec.begin() + idx, val);
	return idx;
}


template<class T>
T get_k_min_abs_value(const std::vector<T>& vec, const size_t& k)
{
	T zero {};
	std::vector<T> saved;

	for (size_t i = 0; i < vec.size(); ++i)
		if (vec[i] != zero)
			insort(saved, std::abs(vec[i]));

	return ((!saved.empty()
			 && (k > 0))
			? saved[std::min(k, vec.size())-1]
			: 0);
}


template<class To, class From>
std::vector<To> reset_type(const std::vector<From>& valuesf)
{
	const size_t len = valuesf.size();
	std::vector<To> valuest(len);
	for (size_t i = 0; i < len; ++i)
		valuest[i] = To(std::round(valuesf[i]));

	return std::move(valuest);
}


template<class T>
::testing::AssertionResult values_are_near(const std::vector<T>& vec1, const std::vector<T>& vec2, const size_t& abs)
{
	if (vec1.size() != vec2.size())
		return ::testing::AssertionFailure()
				<< "vectors' sizes are different: "
				<< vec1.size() << " " << vec2.size();

	for (size_t i = 0; i < vec1.size(); ++i)
		if (roundk((vec1[i] - vec2[i]), abs) != 0.0)
			return ::testing::AssertionFailure()
					<< "different values at " << i << " position, abs: " << abs << std::endl
					<< "  actual: " << vec2[i] << std::endl
					<< "  expected: " << vec1[i];

	return ::testing::AssertionSuccess() << "all values are near with abs: " << abs;
}

#define EXPECT_NEAR_VALUES(vec1, vec2, abs) EXPECT_TRUE(values_are_near(vec1, vec2, abs)) << vec1 << vec2
#define EXPECT_FAR_VALUES(vec1, vec2, abs) EXPECT_FALSE(values_are_near(vec1, vec2, abs)) << vec1 << vec2


// __EXTRA_UTILS_H__
#endif
