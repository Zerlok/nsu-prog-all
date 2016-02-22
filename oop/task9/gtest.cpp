#include <gtest/gtest.h>
#include "heapsort.h"
#include <ctime>
#include <cstdlib>


TEST(HeapSort, Empty)
{
	std::vector<double> empty;
	std::vector<size_t> one = {0};

	ASSERT_NO_THROW({
						heap_sort(empty);
						heap_sort(one);
					});

	EXPECT_TRUE(empty.empty());
	EXPECT_EQ(1, one.size());
	EXPECT_EQ(0, one.front());
}


TEST(HeapSort, Tripples)
{
	std::vector<int> values = {3, 2, 1, 6, 5, 4, 9, 8, 7};

	for (const int& x : values)
		std::cout << x << " ";
	std::cout << std::endl;

	heap_sort(values);

	for (size_t i = 1; i < values.size(); ++i)
		EXPECT_LE(values[i-1], values[i]);

	for (const int& x : values)
		std::cout << x << " ";
	std::cout << std::endl;
}


TEST(HeapSort, WorstInput)
{
	std::vector<int> values = {5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5};

	for (const int& x : values)
		std::cout << x << " ";
	std::cout << std::endl;

	heap_sort(values);

	for (size_t i = 1; i < values.size(); ++i)
		EXPECT_LE(values[i-1], values[i]);

	for (const int& x : values)
		std::cout << x << " ";
	std::cout << std::endl;
}


TEST(HeapSort, BestInput)
{
	std::vector<int> values = {-2, -1, 0, 1, 2, 3};

	for (const int& v : values)
		std::cout << v << " ";
	std::cout << std::endl;

	heap_sort(values);

	for (const int& v : values)
		std::cout << v << " ";
	std::cout << std::endl;
}


TEST(HeapSort, RepeatingData)
{
	std::vector<int> values = {0, 1, 1, 1, 1, 1, 1, 1, 1, 0};

	for (const int& v : values)
		std::cout << v << " ";
	std::cout << std::endl;

	heap_sort(values);

	for (const int& v : values)
		std::cout << v << " ";
	std::cout << std::endl;
}


int main(int argc, char *argv[])
{
	srand(time(NULL));
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
