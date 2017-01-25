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
			: x(1),
			  is_created(b) { is_created = Boolean::TRUE; }
		~Checker() { is_created = Boolean::FALSE; }

		int x;

	private:
		Boolean& is_created;
};


class A
{
	public:
		A() {}
		virtual ~A() {}

		virtual std::string name() { return "A"; }
};


class AA : public A
{
	public:
		AA() : A() {}
		~AA() {}

		std::string name() override { return "AA"; }
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

	EXPECT_EQ(0, p1.get_shares_num());
	EXPECT_EQ(0, p2.get_shares_num());

	p2 = new Empty();
	EXPECT_FALSE(p2.is_null());
	EXPECT_EQ(1, p2.get_shares_num());
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
		EXPECT_EQ(1, p1.get_shares_num());

		p = p1;
		EXPECT_EQ(Boolean::TRUE, is_created1);
		EXPECT_EQ(2, p1.get_shares_num());

		p2 = new Checker(is_created2);
		EXPECT_EQ(Boolean::TRUE, is_created2);
		EXPECT_EQ(1, p2.get_shares_num());

		p = p2;
		EXPECT_EQ(Boolean::TRUE, is_created1);
		EXPECT_EQ(1, p1.get_shares_num());
		EXPECT_EQ(2, p2.get_shares_num());

		p1 = p;
		EXPECT_EQ(Boolean::FALSE, is_created1);
		EXPECT_EQ(3, p1.get_shares_num());
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


/*
TEST(SharedPointer, CopyOnWrite)
{
	SharedPointer<Empty, true> p1, p2;
	p1 = p2 = new Empty();
	const SharedPointer<Empty, true> p3 = p1;
	EXPECT_EQ(3, p3.get_shares_num());

	*(p3);
	EXPECT_EQ(3, p3.get_shares_num());

	*(p1); // calls nonconst operator!
	EXPECT_EQ(1, p1.get_shares_num());
	EXPECT_EQ(2, p2.get_shares_num());
}
*/


std::string lsp_function_base_ptr(A* ptr)
{
	return ptr->name();
}


std::string lsp_function_base_ref(A& obj)
{
	return obj.name();
}


std::string lsp_function_shared_ptr(SharedPointer<A>& ptr)
{
	return ptr->name();
}


TEST(SharedPointer, Inheritance)
{
	SharedPointer<A> ptr1 = new AA();
	SharedPointer<AA, A> ptr2 = new AA();
//	SharedPointer<A> base = ptr2;
	const std::string name = ptr1->name();
	EXPECT_EQ("AA", name);
	EXPECT_EQ(ptr2->name(), name);

	EXPECT_EQ(name, lsp_function_base_ptr(ptr1));
	EXPECT_EQ(name, lsp_function_base_ref(ptr1));
	EXPECT_EQ(name, lsp_function_shared_ptr(ptr1));
	EXPECT_EQ(name, lsp_function_base_ptr(ptr2));
	EXPECT_EQ(name, lsp_function_base_ref(ptr2));
//	EXPECT_EQ(name, lsp_function_shared_ptr(ptr2));
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
