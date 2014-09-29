#include "table.h"
#include <gtest/gtest.h>
#include <iostream>


/* -------------------- STUDENT CLASS TESTS -------------------- */

TEST(Value, Init)
{
	Value a("Danil", 19, 2);
	Value b("Igor", 21, 3, "Physics");

	EXPECT_EQ(a.as_string(), "Danil:(19,2,IT)");
	EXPECT_EQ(b.as_string(), "Igor:(21,3,Physics)");
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
	Item item1("Danil", a), item2("Den", a), item3(a), item4("Den", b);
	
	EXPECT_NE(item1, item2);
	EXPECT_EQ(item1, item3);
	EXPECT_NE(item1, item4);
	EXPECT_NE(item2, item3);
	EXPECT_NE(item2, item4);
}


TEST(Item, Copy)
{
	Value a("Lucy");
	Item item1(a), item2(item1), item3(item2);

	EXPECT_EQ(item1, item2);
	EXPECT_EQ(item2, item3);
	EXPECT_EQ(item1, item3);
}


TEST(Item, OperatorEQEQ)
{
	Value a("Danil"), b("Denis");
	Item item1("Danil", a), item2("Danil2", a), item3(b), item4(b);

	EXPECT_FALSE(item1 == item2);
	EXPECT_FALSE(item1 == item3);
	EXPECT_TRUE(item3 == item4);
}


TEST(Item, Pushback)
{
	Value a("Danil"), b("Bob"), c("Monica");
	Item item1(a), item2(b), item3(c);

	// std::cout << "Inited...";

	EXPECT_TRUE(item1.push_back(item2)) << item1.as_string();
	EXPECT_TRUE(item2.push_back(item3)) << item2.as_string();
	EXPECT_FALSE(item3.push_back(item3)) << item3.as_string();

	// std::cout << "Pushed...";

	EXPECT_EQ(*(item1.get_next()), item2);
	EXPECT_EQ(*(item2.get_next()), item3);
}


/* -------------------- HASHTABLE CLASS TESTS -------------------- */

TEST(HashTable, Init)
{
	HashTable a, b(1);
}


/* Hash func only! */
TEST(HashTable, Collision)
{
	std::cout << "Start...";

	HashTable table(10);

	std::cout << "|...";

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Ivan");

	std::cout << "|...";

	EXPECT_TRUE(table.insert(a.get_name(), a));

	std::cout << "|...";
	
	EXPECT_TRUE(table.insert(b.get_name(), b));

	std::cout << "|...";

	EXPECT_TRUE(table.insert(c.get_name(), c));

	std::cout << "|...";

	EXPECT_EQ(hash(a.get_name()), hash(b.get_name()));
	EXPECT_EQ(table.get_size(), 3);

	std::cout << "|...";
}


TEST(HashTable, CreateFromParent)
{
	HashTable t1;

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Jerry");
	Value d("Lenny");

	t1.insert(a.get_name(), a);
	t1.insert(b.get_name(), b);
	t1.insert(c.get_name(), c);

	HashTable t2(t1);
	

	EXPECT_EQ(t1, t2);

	t2.insert(d.get_name(), d);

	EXPECT_NE(t1, t2);
	EXPECT_EQ(t1.get_size(), 3);
	EXPECT_EQ(t2.get_size(), 4);
}


TEST(HashTable, SizeCounting)
{
	HashTable t1;

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Jerry");
	Value d("Lenny");

	t1.insert(a.get_name(), a);
	t1.insert(b.get_name(), b);
	t1.insert(c.get_name(), c);

	HashTable t2(t1);
	
	t2.insert(d.get_name(), d);

	EXPECT_EQ(t1.get_size(), 3);
	EXPECT_EQ(t2.get_size(), 4);
}


TEST(HashTable, OperatorEQ)
{
	HashTable t1, t2;

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Jerry");
	Value d("Lenny");

	t1.insert(a.get_name(), a);
	t1.insert(b.get_name(), b);
	t1.insert(c.get_name(), c);

	t2 = t1;

	EXPECT_EQ(t1, t2);
}


TEST(HashTable, OperatorEQEQ)
{
	HashTable t1, t2;

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Jerry");
	Value d("Lenny");

	t1.insert(a.get_name(), a);
	t1.insert(b.get_name(), b);
	t1.insert(c.get_name(), c);
	
	t2.insert(a.get_name(), a);
	
	t1.insert(d.get_name(), d);

	t2.insert(b.get_name(), b);
	t2.insert(c.get_name(), c);
	t2.insert(d.get_name(), d);

	EXPECT_TRUE(t1.is_contains(b.get_name()));
	EXPECT_TRUE(t2.is_contains(b.get_name()));
	EXPECT_TRUE(t1.is_contains(c.get_name()));
	EXPECT_TRUE(t2.is_contains(c.get_name()));
	EXPECT_TRUE(t1 == t2);
}


TEST(HashTable, Empty)
{
	HashTable t1;

	EXPECT_EQ(t1.get_size(), 0);
	EXPECT_TRUE(t1.is_empty());
}


TEST(HashTable, Insert)
{
	HashTable t1, t2, t3;

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Jerry");
	Value d("Lenny");
	Value e("Jeffy"); // Collision with c

	t1.insert(a.get_name(), a);
	t1.insert(a.get_name(), a); // Again
	t1.insert(b.get_name(), b);
	t1.insert(c.get_name(), c);
	t1.insert(e.get_name(), e);
	
	t2.insert(a.get_name(), a);
	
	EXPECT_TRUE(t1.is_contains(a.get_name()));
	EXPECT_TRUE(t1.is_contains(b.get_name()));
	EXPECT_TRUE(t1.is_contains(c.get_name()));
	EXPECT_FALSE(t1.is_contains(d.get_name()));
	EXPECT_TRUE(t1.is_contains(e.get_name()));
	EXPECT_EQ(t1.get_size(), 4);

	EXPECT_TRUE(t2.is_contains(a.get_name()));
	EXPECT_FALSE(t2.is_contains(b.get_name()));
	EXPECT_FALSE(t2.is_contains(d.get_name()));
	EXPECT_EQ(t2.get_size(), 1);

	EXPECT_TRUE(t3.is_empty());
}


TEST(HashTable, Erase)
{
	HashTable t1, t2;

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Jerry");
	Value d("Lenny");
	Value e("Jeffy"); // Collision with c

	t1.insert(a.get_name(), a);
	t1.insert(b.get_name(), b);
	t1.insert(c.get_name(), c);
	t1.insert(e.get_name(), e);
	
	t2.insert(a.get_name(), a);
	t2.insert(e.get_name(), e);

	t1.erase(c.get_name());
	EXPECT_TRUE(t1.is_contains(a.get_name()));
	EXPECT_TRUE(t1.is_contains(b.get_name()));
	EXPECT_FALSE(t1.is_contains(c.get_name()));
	EXPECT_FALSE(t1.is_contains(d.get_name()));

	t2.erase(c.get_name());
	EXPECT_TRUE(t2.is_contains(a.get_name()));
	EXPECT_FALSE(t2.is_contains(b.get_name()));
	EXPECT_FALSE(t2.is_contains(d.get_name()));
	EXPECT_TRUE(t2.is_contains(e.get_name()));

	t1.erase(a.get_name());
	EXPECT_FALSE(t1.is_contains(a.get_name()));
	EXPECT_TRUE(t1.is_contains(b.get_name()));
	EXPECT_FALSE(t1.is_contains(c.get_name()));
	EXPECT_FALSE(t1.is_contains(d.get_name()));

	t2.erase(a.get_name());
	t2.erase(e.get_name());

	EXPECT_EQ(t1.get_size(), 2);
	EXPECT_EQ(t2.get_size(), 0);
}


TEST(HashTable, Clear)
{
	HashTable t1, t2, t3;

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Jerry");
	Value d("Lenny");
	Value e("Jeffy"); // Collision with c

	t1.insert(a.get_name(), a);
	t1.insert(b.get_name(), b);
	t1.insert(c.get_name(), c);
	t1.insert(e.get_name(), e);

	t2.insert(a.get_name(), a);
	t2.insert(e.get_name(), e);

	t1.clear();
	EXPECT_FALSE(t1.is_contains(a.get_name()));
	EXPECT_FALSE(t1.is_contains(b.get_name()));
	EXPECT_FALSE(t1.is_contains(c.get_name()));
	EXPECT_FALSE(t1.is_contains(d.get_name()));
	EXPECT_FALSE(t1.is_contains(e.get_name()));

	t2.clear();
	EXPECT_FALSE(t2.is_contains(a.get_name()));
	EXPECT_FALSE(t2.is_contains(b.get_name()));
	EXPECT_FALSE(t2.is_contains(d.get_name()));
	EXPECT_FALSE(t2.is_contains(e.get_name()));

	EXPECT_TRUE(t3.is_empty());
	t3.clear();
	
	EXPECT_EQ(t1.get_size(), 0);
	EXPECT_EQ(t2.get_size(), 0);
	EXPECT_EQ(t3.get_size(), 0);
}


TEST(HashTable, Swap)
{
	HashTable t1, t2, t3, t4;

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Jerry");
	Value d("Lenny");
	Value e("Jeffy"); // Collision with c

	t1.insert(a.get_name(), a);
	t1.insert(b.get_name(), b);
	t1.insert(c.get_name(), c);
	t1.insert(e.get_name(), e);

	t2.insert(a.get_name(), a);
	t2.insert(e.get_name(), e);

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

	EXPECT_TRUE(t3.is_contains(a.get_name()));
	EXPECT_TRUE(t3.is_contains(b.get_name()));
	EXPECT_TRUE(t3.is_contains(c.get_name()));
	EXPECT_FALSE(t3.is_contains(d.get_name()));

	EXPECT_TRUE(t4.is_contains(a.get_name()));
	EXPECT_FALSE(t4.is_contains(b.get_name()));
	EXPECT_FALSE(t4.is_contains(d.get_name()));
	EXPECT_TRUE(t4.is_contains(e.get_name()));
}


TEST(HashTable, OperatorBrackets)
{
	HashTable t1, t2;

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Jerry");
	Value d("Lenny");
	Value e("Jeffy"); // Collision with c

	t1.insert(a.get_name(), a);
	t1.insert(b.get_name(), b);
	t1.insert(c.get_name(), c);
	t1.insert(e.get_name(), e);

	t2.insert(a.get_name(), a);
	t2.insert(e.get_name(), e);

	EXPECT_EQ(t1[a.get_name()], a);
	EXPECT_EQ(t1[b.get_name()], b);
	EXPECT_EQ(t1.get_size(), 4);
	
	EXPECT_EQ(t2[d.get_name()], d);
	EXPECT_EQ(t2.get_size(), 3);
	EXPECT_TRUE(t2.is_contains(d.get_name()));
}


TEST(HashTable, Get)
{
	HashTable t1;

	Value a("Danil");
	Value b("Diman"); // Collision with a
	Value c("Jerry");
	Value d("Lenny");
	Value e("Jeffy"); // Collision with c

	t1.insert(a.get_name(), a);
	t1[b.get_name()];
	t1[c.get_name()];

	EXPECT_EQ(t1.get(a.get_name()), a);
	EXPECT_EQ(t1.get(b.get_name()), b);
	EXPECT_THROW(t1.get(d.get_name()), std::exception);
}


/* -------------------- MAIN -------------------- */

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}