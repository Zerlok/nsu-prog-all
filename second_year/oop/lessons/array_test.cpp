#include "autopointer.h"
#include <gtest/gtest.h>


TEST(ArrayTest, CreateEmpty)
{
	int len = 0;
	Array arr1(len);
	
	EXPECT_EQ(arr1.len(), 0) << "Array: " << arr1;
}

TEST(ArrayTest, InsertToEmpty)
{
	int len = 1;
	Array arr1(len);

	arr1.insert(0, 5);
	
	EXPECT_EQ(arr1[0], 5) << "Array: " << arr1;
	EXPECT_EQ(arr1.len(), 1) << "Array: " << arr1;
}

TEST(ArrayTest, InsertToCenter)
{
	int len = 5;
	Array arr1(10);

	for (int i = 1; i < 5; i++)
	{
		arr1.push_back(i);
	}
	
	arr1.insert(2, 5);

	EXPECT_EQ(arr1[2], 5) << "Array: " << arr1;
	EXPECT_EQ(arr1.len(), 5) << "Array: " << arr1;
}

TEST(ArrayTest, ComparingEmpties)
{
	int len = 5;
	Array arr1(0), arr2(0); 

	EXPECT_EQ(arr1==arr2, 1) << "Array1: " << arr1  << "Array2: " << arr2;
}

TEST(ArrayTest, Comparing)
{
	int len = 5;
	Array arr1(len), arr2(len);

	for (int i = 0; i < len; i++)
	{
		arr1.push_back(i);
		arr2.push_back(i);	
	}

	EXPECT_EQ(arr1==arr2, 1) << "Array1: " << arr1  << "Array2: " << arr2;
}

TEST(ArrayTest, Copy)
{
	int len = 5;
	Array arr1(len), arr2(0);

	for (int i = 0; i < len; i++)
	{
		arr1.push_back(i);
	}

	arr2 = arr1;

	EXPECT_EQ(arr1==arr2, 1) << "Array1: " << arr1  << "Array2: " << arr2;
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}