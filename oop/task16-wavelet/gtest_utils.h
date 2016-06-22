#ifndef __GTEST_UTILS_H__
#define __GTEST_UTILS_H__


#include <iostream>
#include <vector>
#include <gtest/gtest.h>

#include "utils.h"


template<class T>
::testing::AssertionResult values_are_near(const T& data1, const T& data2, const size_t& abs)
{
	if (data1.size() != data2.size())
		return ::testing::AssertionFailure()
				<< "containers' sizes are different: "
				<< data1.size() << " " << data2.size();

	for (size_t i = 0; i < data1.size(); ++i)
		if (roundk((data1[i] - data2[i]), abs) != 0.0)
			return ::testing::AssertionFailure()
					<< "different values at " << i << " position, abs: " << abs << std::endl
					<< "  actual: " << data2[i] << std::endl
					<< "  expected: " << data1[i];

	return ::testing::AssertionSuccess() << "all values are near with abs: " << abs;
}
#define EXPECT_NEAR_VALUES(vec1, vec2, abs) EXPECT_TRUE(values_are_near(vec1, vec2, abs)) << vec1 << vec2
#define EXPECT_FAR_VALUES(vec1, vec2, abs) EXPECT_FALSE(values_are_near(vec1, vec2, abs)) << vec1 << vec2





// __GTEST_UTILS_H__
#endif
