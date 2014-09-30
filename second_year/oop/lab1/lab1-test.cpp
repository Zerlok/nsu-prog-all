#include "table.h"
#include <gtest/gtest.h>
#include <iostream>


#ifdef __HTABLE_DEBUG__

/* -------------------- STUDENT CLASS TESTS -------------------- */

TEST(Value, Init)
{
	Value a("Danil", 19, 2);
	Value b("Igor", 21, 3, "Physics");
}


TEST(Value, Copy)
{
	Value a("Danil"), b(a);

	EXPECT_EQ(a, b);
}


TEST(Value, OperatorEQEQ)
{
	Value a("Danil");
	Value b(a);
	Value c("Danil");
	Value d("Danil", 19);

	EXPECT_TRUE(a == b);
	EXPECT_TRUE(a == c);
	EXPECT_FALSE(a == d);
	EXPECT_FALSE(b == d);
}


/* -------------------- ITEM CLASS TESTS -------------------- */

TEST(Item, Init)
{
	Value a("Danil");
	Value b("Merlin");
	Item item1("Danil", a), item2("Den", a), item3("Danil", a), item4("Den", b);
	
	EXPECT_NE(item1, item2);
	EXPECT_EQ(item1, item3);
	EXPECT_NE(item1, item4);
	EXPECT_NE(item2, item3);
	EXPECT_NE(item2, item4);
}


TEST(Item, Copy)
{
	Value a("Lucy");
	Item item1("she", a), item2(item1), item3(item2);

	EXPECT_EQ(item1, item2);
	EXPECT_EQ(item2, item3);
	EXPECT_EQ(item1, item3);
}


TEST(Item, OperatorEQEQ)
{
	Value a("Danil"), b("Denis");
	Item item1("Danil", a), item2("Danil2", a), item3("Denis", b), item4("Denis", b);

	EXPECT_FALSE(item1 == item2);
	EXPECT_FALSE(item1 == item3);
	EXPECT_TRUE(item3 == item4);
}


TEST(Item, Pushback)
{
	Value a("Danil"), b("Bob"), c("Monica");
	Item item1("1", a), item2("2", b), item3("3", c);

	EXPECT_TRUE(item1.push_back(&item2));
	EXPECT_TRUE(item2.push_back(&item3));
	EXPECT_FALSE(item3.push_back(&item3));

	EXPECT_EQ(*(item1.get_next()), item2);
	EXPECT_EQ(*(item2.get_next()), item3);
}


/* TEST PASSES WHEN DEBUG IS ON!!! */
TEST(HashTable, Collision)
{
	HashTable table(10);

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Ivan");

	EXPECT_TRUE(table.insert(a.return_name(), a));
	EXPECT_TRUE(table.insert(b.return_name(), b));
	EXPECT_TRUE(table.insert(c.return_name(), c));
	EXPECT_EQ(hash(a.return_name()), hash(b.return_name()));
	EXPECT_EQ(table.get_size(), 3);
}

#endif

/* -------------------- HASHTABLE CLASS TESTS -------------------- */

TEST(HashTable, Init)
{
	ASSERT_NO_THROW(HashTable a);
	ASSERT_NO_THROW(HashTable b(1));
	
	EXPECT_THROW(
	{
		HashTable c(-1);
	},
	std::invalid_argument);
}


TEST(HashTable, CreateFromParent)
{
	HashTable t1;

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Jerry");
	Value d("Lenny");

	ASSERT_TRUE(t1.insert(a.return_name(), a));
	ASSERT_TRUE(t1.insert(b.return_name(), b));
	ASSERT_TRUE(t1.insert(c.return_name(), c));

	HashTable t2(t1), t3(4), t4(t3);

	EXPECT_EQ(t1, t2);

	ASSERT_TRUE(t2.insert(d.return_name(), d));

	EXPECT_NE(t1, t2);
	EXPECT_EQ(t3, t4);
	EXPECT_EQ(t1.get_size(), 3);
	EXPECT_EQ(t2.get_size(), 4);
	EXPECT_TRUE(t3.is_empty());
	EXPECT_TRUE(t4.is_empty());
}


TEST(HashTable, SizeCounting)
{
	HashTable t1;

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Jerry");
	Value d("Lenny");

	ASSERT_TRUE(t1.insert(a.return_name(), a));
	ASSERT_TRUE(t1.insert(b.return_name(), b));
	ASSERT_TRUE(t1.insert(c.return_name(), c));

	HashTable t2(t1), t3(7);
	
	ASSERT_TRUE(t2.insert(d.return_name(), d));

	EXPECT_EQ(t1.get_size(), 3);
	EXPECT_EQ(t2.get_size(), 4);
	EXPECT_EQ(t3.get_size(), 0);
}


TEST(HashTable, OperatorEQ)
{
	HashTable t1, t2, t3(8), t4(2);

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Jerry");
	Value d("Lenny");

	ASSERT_TRUE(t1.insert(a.return_name(), a));
	ASSERT_TRUE(t1.insert(b.return_name(), b));
	ASSERT_TRUE(t1.insert(c.return_name(), c));

	ASSERT_TRUE(t2.insert(d.return_name(), d));

	EXPECT_NO_THROW(
	{
		t2 = t1;
	});

	EXPECT_FALSE(t2.is_contains(d.return_name()));

	EXPECT_EQ(t1, t2);

	EXPECT_NO_THROW(
	{
		t1 = t2;
	});

	EXPECT_EQ(t1, t2);

	EXPECT_NO_THROW(
	{
		t1 = t3;
		t4 = t2;
	});

	EXPECT_EQ(t1, t3);
	EXPECT_EQ(t4, t2);
}


TEST(HashTable, OperatorEQEQ)
{
	HashTable t1, t2, t3(3), t4(7);

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Jerry");
	Value d("Lenny");

	ASSERT_TRUE(t1.insert(a.return_name(), a));
	ASSERT_TRUE(t1.insert(b.return_name(), b));
	ASSERT_TRUE(t1.insert(c.return_name(), c));
	
	ASSERT_TRUE(t2.insert(a.return_name(), a));
	
	ASSERT_TRUE(t1.insert(d.return_name(), d));

	ASSERT_TRUE(t2.insert(b.return_name(), b));
	ASSERT_TRUE(t2.insert(c.return_name(), c));
	ASSERT_TRUE(t2.insert(d.return_name(), d));

	EXPECT_TRUE(t1.is_contains(b.return_name()));
	EXPECT_TRUE(t2.is_contains(b.return_name()));
	EXPECT_TRUE(t1.is_contains(c.return_name()));
	EXPECT_TRUE(t2.is_contains(c.return_name()));
	EXPECT_TRUE(t1 == t2);

	EXPECT_FALSE(t3 == t4);
	ASSERT_TRUE(t3.insert(c.return_name(), c));
	ASSERT_TRUE(t4.insert(b.return_name(), b));
	EXPECT_FALSE(t3 == t4);
}


TEST(HashTable, Empty)
{
	HashTable t1, t2(5);

	EXPECT_EQ(t1.get_size(), 0);
	EXPECT_TRUE(t1.is_empty());

	EXPECT_EQ(t2.get_size(), 0);
	EXPECT_TRUE(t2.is_empty());
}


TEST(HashTable, Insert)
{
	HashTable t1(3), t2(17), t3;

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Jerry");
	Value d("Lenny");
	Value e("Jeffy"); // Collision with c

	EXPECT_TRUE(t1.insert(a.return_name(), a));
	EXPECT_FALSE(t1.insert(a.return_name(), a)); // Again - fails (this key exists).
	EXPECT_TRUE(t1.insert(b.return_name(), b));
	EXPECT_TRUE(t1.insert(c.return_name(), c));
	EXPECT_TRUE(t1.insert(e.return_name(), e));
	
	EXPECT_TRUE(t2.insert(a.return_name(), a));
	
	EXPECT_TRUE(t1.is_contains(a.return_name()));
	EXPECT_TRUE(t1.is_contains(b.return_name()));
	EXPECT_TRUE(t1.is_contains(c.return_name()));
	EXPECT_FALSE(t1.is_contains(d.return_name()));
	EXPECT_TRUE(t1.is_contains(e.return_name()));
	EXPECT_EQ(t1.get_size(), 4);

	EXPECT_TRUE(t2.is_contains(a.return_name()));
	EXPECT_FALSE(t2.is_contains(b.return_name()));
	EXPECT_FALSE(t2.is_contains(d.return_name()));
	EXPECT_EQ(t2.get_size(), 1);

	EXPECT_TRUE(t3.is_empty());
}


TEST(HashTable, Erase)
{
	HashTable t1(7), t2;

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Jerry");
	Value d("Lenny");
	Value e("Jeffy"); // Collision with c

	ASSERT_TRUE(t1.insert(a.return_name(), a));
	ASSERT_TRUE(t1.insert(b.return_name(), b));
	ASSERT_TRUE(t1.insert(c.return_name(), c));
	ASSERT_TRUE(t1.insert(e.return_name(), e));
	
	ASSERT_TRUE(t2.insert(a.return_name(), a));
	ASSERT_TRUE(t2.insert(e.return_name(), e));

	EXPECT_TRUE(t1.erase(c.return_name()));
	EXPECT_TRUE(t1.is_contains(a.return_name()));
	EXPECT_TRUE(t1.is_contains(b.return_name()));
	EXPECT_FALSE(t1.is_contains(c.return_name()));
	EXPECT_FALSE(t1.is_contains(d.return_name()));

	EXPECT_FALSE(t2.erase(c.return_name()));
	EXPECT_TRUE(t2.is_contains(a.return_name()));
	EXPECT_FALSE(t2.is_contains(b.return_name()));
	EXPECT_FALSE(t2.is_contains(d.return_name()));
	EXPECT_TRUE(t2.is_contains(e.return_name()));

	EXPECT_TRUE(t1.erase(a.return_name()));
	EXPECT_FALSE(t1.is_contains(a.return_name()));
	EXPECT_TRUE(t1.is_contains(b.return_name()));
	EXPECT_FALSE(t1.is_contains(c.return_name()));
	EXPECT_FALSE(t1.is_contains(d.return_name()));

	EXPECT_TRUE(t2.erase(a.return_name()));
	EXPECT_TRUE(t2.erase(e.return_name()));

	EXPECT_FALSE(t2.erase(a.return_name()));

	EXPECT_EQ(t1.get_size(), 2);
	EXPECT_EQ(t2.get_size(), 0);
}


TEST(HashTable, Clear)
{
	HashTable t1, t2(3), t3;

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Jerry");
	Value d("Lenny");
	Value e("Jeffy"); // Collision with c

	ASSERT_TRUE(t1.insert(a.return_name(), a));
	ASSERT_TRUE(t1.insert(b.return_name(), b));
	ASSERT_TRUE(t1.insert(c.return_name(), c));
	ASSERT_TRUE(t1.insert(e.return_name(), e));

	ASSERT_TRUE(t2.insert(a.return_name(), a));
	ASSERT_TRUE(t2.insert(e.return_name(), e));

	t1.clear();
	EXPECT_FALSE(t1.is_contains(a.return_name()));
	EXPECT_FALSE(t1.is_contains(b.return_name()));
	EXPECT_FALSE(t1.is_contains(c.return_name()));
	EXPECT_FALSE(t1.is_contains(d.return_name()));
	EXPECT_FALSE(t1.is_contains(e.return_name()));

	t2.clear();
	EXPECT_FALSE(t2.is_contains(a.return_name()));
	EXPECT_FALSE(t2.is_contains(b.return_name()));
	EXPECT_FALSE(t2.is_contains(d.return_name()));
	EXPECT_FALSE(t2.is_contains(e.return_name()));

	EXPECT_TRUE(t3.is_empty());
	t3.clear();
	
	EXPECT_EQ(t1.get_size(), 0);
	EXPECT_EQ(t2.get_size(), 0);
	EXPECT_EQ(t3.get_size(), 0);
}


TEST(HashTable, Swap)
{
	HashTable t1, t2(11), t3(13), t4;

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Jerry");
	Value d("Lenny");
	Value e("Jeffy"); // Collision with c

	ASSERT_TRUE(t1.insert(a.return_name(), a));
	ASSERT_TRUE(t1.insert(b.return_name(), b));
	ASSERT_TRUE(t1.insert(c.return_name(), c));
	ASSERT_TRUE(t1.insert(e.return_name(), e));

	ASSERT_TRUE(t2.insert(a.return_name(), a));
	ASSERT_TRUE(t2.insert(e.return_name(), e));

	t1.swap(t2);
	EXPECT_EQ(t1.get_size(), 2);
	EXPECT_EQ(t2.get_size(), 4);

	t3.swap(t4);
	EXPECT_TRUE(t3.is_empty());
	EXPECT_TRUE(t4.is_empty());

	t1.swap(t4);
	EXPECT_TRUE(t1.is_empty());
	EXPECT_EQ(t4.get_size(), 2);

	t2.swap(t3);
	EXPECT_TRUE(t2.is_empty());
	EXPECT_EQ(t3.get_size(), 4);

	EXPECT_TRUE(t3.is_contains(a.return_name()));
	EXPECT_TRUE(t3.is_contains(b.return_name()));
	EXPECT_TRUE(t3.is_contains(c.return_name()));
	EXPECT_FALSE(t3.is_contains(d.return_name()));

	EXPECT_TRUE(t4.is_contains(a.return_name()));
	EXPECT_FALSE(t4.is_contains(b.return_name()));
	EXPECT_FALSE(t4.is_contains(d.return_name()));
	EXPECT_TRUE(t4.is_contains(e.return_name()));
}


TEST(HashTable, OperatorBrackets)
{
	HashTable t1, t2;

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Jerry");
	Value d("Lenny");
	Value e("Jeffy"); // Collision with c

	ASSERT_TRUE(t1.insert(a.return_name(), a));
	ASSERT_TRUE(t1.insert(b.return_name(), b));
	ASSERT_TRUE(t1.insert(c.return_name(), c));
	ASSERT_TRUE(t1.insert(e.return_name(), e));

	ASSERT_TRUE(t2.insert(a.return_name(), a));
	ASSERT_TRUE(t2.insert(e.return_name(), e));

	EXPECT_EQ(t1[a.return_name()], a); // Gets.
	EXPECT_EQ(t1[b.return_name()], b); // Inserts.
	EXPECT_EQ(t1.get_size(), 4);
	
	EXPECT_EQ(t2[d.return_name()], d); // Inserts.
	EXPECT_EQ(t2.get_size(), 3);
	EXPECT_TRUE(t2.is_contains(d.return_name()));
}


TEST(HashTable, Get)
{
	HashTable t1;

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Jerry");
	Value d("Lenny");
	Value e("Jeffy"); // Collision with c

	ASSERT_TRUE(t1.insert(a.return_name(), a));
	ASSERT_EQ(t1[b.return_name()], b);
	ASSERT_EQ(t1[c.return_name()], c);

	EXPECT_EQ(t1.get(a.return_name()), a);
	EXPECT_EQ(t1.get(b.return_name()), b);
	EXPECT_THROW(t1.get(d.return_name()), std::exception);
}


TEST(Common, HashTable)
{
	HashTable t1(1), t2(2), t3(4), t4;

	Value a("Danil"), b("Diman"), c("Jerry"), d("Lenny"), e("Jeffy");

	ASSERT_TRUE(t1.is_empty());
	ASSERT_TRUE(t2.is_empty());

	ASSERT_TRUE(t4.insert(b.return_name(), b));
	ASSERT_FALSE(t3.erase(c.return_name())) << t3.get_size() << t3.is_contains(c.return_name());
	ASSERT_TRUE(t4.insert(a.return_name(), a));
	ASSERT_TRUE(t1.insert(e.return_name(), e));

	ASSERT_NO_THROW(t4.clear());
	ASSERT_NO_THROW(t2.clear());

	ASSERT_TRUE(t2.insert(b.return_name(), b));
	ASSERT_FALSE(t2.erase(c.return_name()));
	ASSERT_TRUE(t2.insert(a.return_name(), a));
	ASSERT_TRUE(t2.insert(e.return_name(), e));

	ASSERT_EQ(t3[a.return_name()], a);
	ASSERT_EQ(t4[a.return_name()], a);

	ASSERT_TRUE(t4.is_contains(a.return_name()));
	ASSERT_FALSE(t3.is_contains(e.return_name()));

	EXPECT_NO_THROW(t2["my"] = b);
	EXPECT_EQ(t2.get("my"), b);

	EXPECT_NO_THROW(t2[a.return_name()] = b);
	EXPECT_EQ(t2.get(a.return_name()), b);
}


/* -------------------- MAIN -------------------- */

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}