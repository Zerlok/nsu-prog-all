#include "array.h"
#include <gtest/gtest.h>


TEST(ArrayTest, FirstTest)
{
	Array arr1(10), arr2(20);

	for (int i = 1; i < 5; i++)
	{
		arr1.push_back(i);
	}

	arr1.show();
	arr2 = arr1;
	
	arr1.insert(2, -100);

	arr1.show();
	arr2.show();

	EXPECT_EQ(arr1==arr2, 0) << "A1: " << arr1 << " A2: " << arr2;
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}