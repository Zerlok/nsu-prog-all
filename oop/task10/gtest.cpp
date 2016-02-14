#include <gtest/gtest.h>
#include <algorithm>
#include "filteriterator.h"


class Greater
{
	public:
		Greater(const int value = 0)
			: _val(value) {}

		bool operator()(const int x) const { return x > _val; }

	private:
		const int _val;
};


TEST(FilterIterator, Filter)
{
	const int z = -1;

	std::vector<int> values = {-3, 5, -4, 11, -1, -8, -8, 0, 31, -1};
	std::vector<int> filtered;

	std::copy(
//			values.begin(),
			FilterIterator<std::vector<int>::iterator, Greater>(values.begin(), values.end(), Greater(z)),
			values.end(),
			std::back_inserter(filtered)
	);

	for (int n : filtered)
		EXPECT_GT(n, z);
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
