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


TEST(SharedPointer, InitRelease)
{
	Boolean is_created = Boolean::FALSE;

	SharedPointer<Checker> p(new Checker(is_created));
	EXPECT_EQ(Boolean::TRUE, is_created);

	p.release();
	EXPECT_EQ(Boolean::FALSE, is_created);
}


TEST(SharedPointer, Nullpointer)
{
	SharedPointer<Empty> p1;
	EXPECT_TRUE(p1.is_null());

	p1 = nullptr;
	EXPECT_TRUE(p1.is_null());
	EXPECT_EQ(nullptr, p1.get_pointer());

	SharedPointer<Empty> p2 = p1;
	EXPECT_TRUE(p2.is_null());
	EXPECT_EQ(nullptr, p2.get_pointer());

	EXPECT_EQ(0, p1.get_references_counter());
	EXPECT_EQ(0, p2.get_references_counter());

	p2 = new Empty();
	EXPECT_FALSE(p2.is_null());
	EXPECT_EQ(1, p2.get_references_counter());
}


TEST(SharedPointer, VectorData)
{
	std::vector<Boolean> booleans(5, Boolean::FALSE);

	{
		std::vector<SharedPointer<Checker> > values(booleans.size());

		for (size_t i = 0; i < values.size(); ++i)
		{
			EXPECT_TRUE(values[i].is_null());
			values[i] = new Checker(booleans[i]);
			EXPECT_FALSE(values[i].is_null());
		}

		for (const Boolean& b : booleans)
			EXPECT_EQ(Boolean::TRUE, b);
	}

	for (const Boolean& b : booleans)
		EXPECT_EQ(Boolean::FALSE, b);
}


TEST(SharedPointer, CopyEq)
{
	Boolean is_created1 = Boolean::FALSE;
	Boolean is_created2 = Boolean::FALSE;

	{
		SharedPointer<Checker> p1, p2, p;
		p1 = new Checker(is_created1);
		EXPECT_EQ(Boolean::TRUE, is_created1);
		EXPECT_EQ(1, p1.get_references_counter());

		p = p1;
		EXPECT_EQ(Boolean::TRUE, is_created1);
		EXPECT_EQ(2, p1.get_references_counter());

		p2 = new Checker(is_created2);
		EXPECT_EQ(Boolean::TRUE, is_created2);
		EXPECT_EQ(1, p2.get_references_counter());

		p = p2;
		EXPECT_EQ(Boolean::TRUE, is_created1);
		EXPECT_EQ(1, p1.get_references_counter());
		EXPECT_EQ(2, p2.get_references_counter());

		p1 = p;
		EXPECT_EQ(Boolean::FALSE, is_created1);
		EXPECT_EQ(3, p1.get_references_counter());
	}

	EXPECT_EQ(Boolean::FALSE, is_created1);
}


TEST(SharedPointer, Move)
{
	Boolean is_created = Boolean::FALSE;

	SharedPointer<Checker> p1(new Checker(is_created));
	SharedPointer<Checker> p2;
	EXPECT_EQ(Boolean::TRUE, is_created);
	EXPECT_FALSE(p1.is_null());
	EXPECT_TRUE(p2.is_null());

	p2 = std::move(p1);
	EXPECT_EQ(Boolean::TRUE, is_created);
	EXPECT_TRUE(p1.is_null());
	EXPECT_FALSE(p2.is_null());
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
