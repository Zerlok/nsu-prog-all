#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <list>
#include <functional>
#include "filteriterator.h"


TEST(FilterIterator, Init)
{
	std::list<int> lst = {-1, 0, 1, -1, 0, 1};
	std::list<char> empty_lst;

	auto fiter1 = make_filter_iterator(lst.begin(), lst.end(), [](const int x) { return x > 0; });
	EXPECT_TRUE(fiter1.is_predicate());

	auto fiter2 = make_filter_iterator(empty_lst.begin(), empty_lst.end(), [](const int x) { return x > 0; });
	EXPECT_FALSE(fiter2.is_predicate());
	EXPECT_EQ(fiter2, empty_lst.end());
}


TEST(FilterIterator, BeginEnd)
{
	std::vector<int> v = {1};
	auto g0fiter = make_filter_iterator(v.begin(), v.end(), [](const int x) { return x > 0; });
	auto g1fiter = make_filter_iterator(v.begin(), v.end(), [](const int x) { return x > 1; });

	EXPECT_EQ(g0fiter, v.begin());
	EXPECT_EQ(g1fiter, v.end());
}


TEST(FilterIterator, Filter)
{
	const int z = 0;

	std::vector<int> values = {-3, 5, -4, 11, -1, -8, -8, 0, 31, -1, 92};
	std::vector<int> positive, negative;

	// Get all positives.
	for (auto it = make_filter_iterator(values.begin(), values.end(), [&z](const int x) { return x > z; });
		 it != values.end();
		 ++it)
		positive.push_back(*it);

	// Get all negatives.
	for (auto it = make_filter_iterator(values.begin(), values.end(), [&z](const int x) { return x <= z; });
		 it != values.end();
		 ++it)
		negative.push_back(*it);

	// Check positives.
	for (int n : positive)
		EXPECT_GT(n, z);

	// Check negatives.
	for (int n : negative)
		EXPECT_LE(n, z);

	// Check no missing values.
	positive.insert(positive.end(), negative.begin(), negative.end());
	EXPECT_EQ(values.size(), positive.size());
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
