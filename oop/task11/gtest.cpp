#include <gtest/gtest.h>
#include <vector>
#include "sharedpointer.h"


enum class Boolean
{
	FALSE = false,
	TRUE = true,
};

class Empty {};

class Checker
{
	public:
		Checker(Boolean& b)
			: is_created(b),
			  x(1) { is_created = Boolean::TRUE; }
		~Checker() { is_created = Boolean::FALSE; }

		int x;

	private:
		Boolean& is_created;
};


TEST(SharedPointer, Null)
{
	SharedPointer<int> p1;
	EXPECT_TRUE(p1.is_null());

	p1 = nullptr;
	EXPECT_EQ(nullptr, p1.get_pointer());

	SharedPointer<int> p2 = p1;

	EXPECT_TRUE(p1.is_null());
	EXPECT_TRUE(p2.is_null());
	EXPECT_EQ(nullptr, p1.get_pointer());
	EXPECT_EQ(nullptr, p2.get_pointer());
}


TEST(SharedPointer, VectorEmpty)
{
	std::vector<SharedPointer<Empty> > empties(10);

	for (SharedPointer<Empty>& p : empties)
	{
		EXPECT_TRUE(p.is_null());
		p = new Empty();
		EXPECT_FALSE(p.is_null());
	}

	for (SharedPointer<Empty> p : empties)
	{
		p.reset();
		EXPECT_TRUE(p.is_null());
	}
}


TEST(SharedPointer, VectorData)
{
	std::vector<Boolean> booleans(10, Boolean::FALSE);

	for (const Boolean& b : booleans)
		EXPECT_EQ(Boolean::FALSE, b);

	{
		std::vector<SharedPointer<Checker> > values(booleans.size());

		for (size_t i = 0; i < values.size(); ++i)
			values[i] = new Checker(booleans[i]);

		for (const Boolean& b : booleans)
			EXPECT_EQ(Boolean::TRUE, b);
	}

	for (const Boolean& b : booleans)
		EXPECT_EQ(Boolean::FALSE, b);
}


TEST(SharedPointer, Copy)
{
	Boolean is_good = Boolean::FALSE;

	{
		std::vector<SharedPointer<Checker> > pointers(10);
		pointers.front() = new Checker(is_good);
		EXPECT_EQ(Boolean::TRUE, is_good);

		EXPECT_FALSE(pointers.front().is_null());
		EXPECT_TRUE(pointers.back().is_null());

		for (size_t i = 1; i < pointers.size(); ++i)
			pointers[i] = pointers[i-1];

		EXPECT_EQ(Boolean::TRUE, is_good);
		EXPECT_EQ(pointers.size(), pointers.front().get_references_counter());
	}

	EXPECT_EQ(Boolean::FALSE, is_good);
}


TEST(SharedPointer, Move)
{

}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
