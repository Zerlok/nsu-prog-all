#include <gtest/gtest.h>
#include "sharedpointer.h"
#include <vector>


class Empty {};


class Data
{
	public:
		Data(bool& destroyed)
			: _(destroyed),
			  x(1) { _ = false; }
		~Data() { _ = true; }

		int x;

	private:
		bool& _;
};


TEST(SharedPointer, Null)
{
	SharedPointer<int> p1;
	p1 = nullptr;

	SharedPointer<int> p2 = p1;

	EXPECT_TRUE(p1.is_null());
	EXPECT_TRUE(p2.is_null());
}


TEST(SharedPointer, Vector)
{
	std::vector<SharedPointer<Empty> > empties(10);

	for (SharedPointer<Empty> p : empties)
	{
		EXPECT_TRUE(p.is_null());
		p = new Empty();
	}


}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
