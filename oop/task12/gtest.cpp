#include <gtest/gtest.h>
#include "pool.h"


TEST(ObjectPool, Init)
{
	Pool<int, 1> ints;
	EXPECT_EQ(1, ints.create(1));
}


TEST(ObjectPool, OverflowException)
{
	const size_t n = 5;
	Pool<int, n> ints;

	for (size_t i = 0; i < n; ++i)
		EXPECT_EQ(i, ints.create(i));

	EXPECT_THROW({ ints.create(n); }, PoolOverflowException);
}


TEST(ObjectPool, Empty)
{
	Pool<int, 0> empty;
	EXPECT_THROW({ empty.create(); }, PoolOverflowException);
}


TEST(ObjectPool, Create)
{
	const std::vector<int> v = {1, 2, 3};
	Pool<std::vector<int>, 5> vectors;

	EXPECT_TRUE(vectors.create().empty());
	EXPECT_EQ(v, vectors.create(v));
	EXPECT_EQ(1, vectors.create({3, 2, 1}).back());
}


TEST(ObjectPool, Clear)
{
	Pool<double, 3> doubles;

	doubles.create(0.11);
	double& d = doubles.create(0.22);
	doubles.create(0.33);

	EXPECT_THROW({ doubles.create(0); }, PoolOverflowException);

	doubles.clear(d);
	EXPECT_NO_THROW({ doubles.create(0); });
}


TEST(ObjectPool, IsNotPoolInstanceException)
{
	Pool<int, 1> ints;

	int& zero = ints.create(0);
	EXPECT_EQ(0, zero);

	int a = 1;
	int& a_ref = a;

	EXPECT_NO_THROW({ ints.clear(zero); });
	EXPECT_THROW({ ints.clear(a_ref); }, IsNotPoolInstanceException);
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

