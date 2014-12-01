#include <gtest/gtest.h>


TEST(SmartPointer, Init)
{
	ASSERT_NO_THROW({
		int v = 10;
		int *p = &v;
		
		AutoPointer ap(p);
	});
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}