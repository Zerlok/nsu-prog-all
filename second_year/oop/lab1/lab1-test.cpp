#include "table.h"
#include <gtest/gtest.h>


/* -------------------- STUDENT CLASS TESTS -------------------- */

TEST(Value, Init)
{
	Value a("Danil");
	Value b("Igor", 21, 3, 4.2, "Physics");
	
	EXPECT_EQ(a.get_age(), 18);
	EXPECT_NE(a, b);
}


TEST(Value, Copy)
{
	Value a("Danil"), b(a);
	
	b.set_age(19);

	EXPECT_EQ(a.get_name(), b.get_name());
	EXPECT_NE(a.get_age(), b.get_age());
}


TEST(Value, OperatorEQ)
{
	Value a("Danil");
	Value b("Igor");

	b = a;

	EXPECT_EQ(a.get_name(), b.get_name());
}


TEST(Value, OperatorEQEQ)
{
	Value a("Danil");
	Value b(a);

	EXPECT_TRUE(a == b);
}


/* -------------------- ITEM CLASS TESTS -------------------- */

TEST(Item, Init)
{
	Value a("Danil");
	Item item1("Danil", a), item2("Den"), item3(a);
	
	// item1.show();
	// item2.show();
	// item3.show();

	EXPECT_NE(item1, item2);
	EXPECT_NE(item2, item3);
	EXPECT_EQ(item1, item3);
}


TEST(Item, Copy)
{
	Value a("Danil");
	Item item1(a), item2(item1);

	EXPECT_EQ(item1, item2);
}


TEST(Item, OperatorEQ)
{
	Value a("Den"), b("Jeff");
	Item item1("Danil", a), item2("J", b);

	item2 = item1;

	EXPECT_EQ(item1, item2);
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

	item1.push_back(item2);
	item2.push_back(item3);

	// std::cout << "Pushed...";

	// item1.show();
	// item2.show();
	// item3.show();

	EXPECT_EQ(*(item1.get_next()), item2);
	EXPECT_EQ(*(item2.get_next()), item3);
}


TEST(Item, Empty)
{
	Item item1("empty");

	// item1.show();

	EXPECT_TRUE(item1.is_empty());
}


/* -------------------- HASHTABLE CLASS TESTS -------------------- */

TEST(HashTable, Init)
{
	HashTable a;
}


/* For Hash : key.size() * key[0] */
TEST(HashTable, Collision)
{
	HashTable table(10);

	Value a("Danil");
	Value b("Diman"); // Collision!
	Value c("Ivan");

	a.set_age(19);

	table.insert(a.get_name(), a);
	table.insert(b.get_name(), b);
	table.insert(c.get_name(), c);

	EXPECT_EQ(hash(a.get_name()), hash(b.get_name()));
	EXPECT_EQ(table.size(), 3);
}


TEST(HashTable, CreateFromParent)
{
	HashTable t1;

	Value a("Danil");
	Value b("Diman"); // Collision
	Value c("Jerry");
	Value d("Lenny");

	t1.insert(a.get_name(), a);
	t1.insert(b.get_name(), b);
	t1.insert(c.get_name(), c);

	HashTable t2(t1);
	

	EXPECT_EQ(t1, t2);

	t2.insert(d.get_name(), d);

	EXPECT_NE(t1, t2);
	EXPECT_EQ(t1.size(), 3);
	EXPECT_EQ(t2.size(), 4);
}


TEST(HashTable, SizeCounting)
{
	HashTable t1;

	Value a("Danil");
	Value b("Diman"); // Collision
	Value c("Jerry");
	Value d("Lenny");

	t1.insert(a.get_name(), a);
	t1.insert(b.get_name(), b);
	t1.insert(c.get_name(), c);

	HashTable t2(t1);
	
	t2.insert(d.get_name(), d);

	EXPECT_EQ(t1.size(), 3);
	EXPECT_EQ(t2.size(), 4);
}


TEST(HashTable, OperatorEQ)
{
	HashTable t1, t2;

	Value a("Danil");
	Value b("Diman"); // Collision
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
	Value b("Diman"); // Collision
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

	EXPECT_TRUE(t1.contains(b.get_name()));
	EXPECT_TRUE(t2.contains(b.get_name()));
	EXPECT_TRUE(t1.contains(c.get_name()));
	EXPECT_TRUE(t2.contains(c.get_name()));
	EXPECT_TRUE(t1 == t2);
}


TEST(HashTable, Empty)
{
	HashTable t1;

	EXPECT_EQ(t1.size(), 0);
	EXPECT_TRUE(t1.empty());
}


TEST(HashTable, Insert)
{
	HashTable t1, t2, t3;

	Value a("Danil");
	Value b("Diman"); // Collision
	Value c("Jerry");
	Value d("Lenny");
	Value e("Jeffy"); // Collision with c

	t1.insert(a.get_name(), a);
	t1.insert(a.get_name(), a); // Again
	t1.insert(b.get_name(), b);
	t1.insert(c.get_name(), c);
	t1.insert(e.get_name(), e);
	
	t2.insert(a.get_name(), a);
	
	EXPECT_TRUE(t1.contains(a.get_name()));
	EXPECT_TRUE(t1.contains(b.get_name()));
	EXPECT_TRUE(t1.contains(c.get_name()));
	EXPECT_FALSE(t1.contains(d.get_name()));
	EXPECT_TRUE(t1.contains(e.get_name()));
	EXPECT_EQ(t1.size(), 4);

	EXPECT_TRUE(t2.contains(a.get_name()));
	EXPECT_FALSE(t2.contains(b.get_name()));
	EXPECT_FALSE(t2.contains(d.get_name()));
	EXPECT_EQ(t2.size(), 1);

	EXPECT_TRUE(t3.empty());
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
	EXPECT_TRUE(t1.contains(a.get_name()));
	EXPECT_TRUE(t1.contains(b.get_name()));
	EXPECT_FALSE(t1.contains(c.get_name()));
	EXPECT_FALSE(t1.contains(d.get_name()));

	t2.erase(c.get_name());
	EXPECT_TRUE(t2.contains(a.get_name()));
	EXPECT_FALSE(t2.contains(b.get_name()));
	EXPECT_FALSE(t2.contains(d.get_name()));
	EXPECT_TRUE(t2.contains(e.get_name()));

	t1.erase(a.get_name());
	EXPECT_FALSE(t1.contains(a.get_name()));
	EXPECT_TRUE(t1.contains(b.get_name()));
	EXPECT_FALSE(t1.contains(c.get_name()));
	EXPECT_FALSE(t1.contains(d.get_name()));

	t2.erase(a.get_name());
	t2.erase(e.get_name());

	EXPECT_EQ(t1.size(), 2);
	EXPECT_EQ(t2.size(), 0);
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
	EXPECT_FALSE(t1.contains(a.get_name()));
	EXPECT_FALSE(t1.contains(b.get_name()));
	EXPECT_FALSE(t1.contains(c.get_name()));
	EXPECT_FALSE(t1.contains(d.get_name()));
	EXPECT_FALSE(t1.contains(e.get_name()));

	t2.clear();
	EXPECT_FALSE(t2.contains(a.get_name()));
	EXPECT_FALSE(t2.contains(b.get_name()));
	EXPECT_FALSE(t2.contains(d.get_name()));
	EXPECT_FALSE(t2.contains(e.get_name()));

	EXPECT_TRUE(t3.empty());
	t3.clear();
	
	EXPECT_EQ(t1.size(), 0);
	EXPECT_EQ(t2.size(), 0);
	EXPECT_EQ(t3.size(), 0);
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
	EXPECT_EQ(t1.size(), 2);
	EXPECT_EQ(t2.size(), 4);

	t3.swap(t4);
	EXPECT_TRUE(t3.empty());
	EXPECT_TRUE(t4.empty());

	t1.swap(t4);
	EXPECT_TRUE(t1.empty());
	EXPECT_EQ(t4.size(), 2);

	t2.swap(t3);
	EXPECT_TRUE(t2.empty());
	EXPECT_EQ(t3.size(), 4);

	EXPECT_TRUE(t3.contains(a.get_name()));
	EXPECT_TRUE(t3.contains(b.get_name()));
	EXPECT_TRUE(t3.contains(c.get_name()));
	EXPECT_FALSE(t3.contains(d.get_name()));

	EXPECT_TRUE(t4.contains(a.get_name()));
	EXPECT_FALSE(t4.contains(b.get_name()));
	EXPECT_FALSE(t4.contains(d.get_name()));
	EXPECT_TRUE(t4.contains(e.get_name()));
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
	EXPECT_EQ(t1.size(), 4);
	
	EXPECT_EQ(t2[d.get_name()], d);
	EXPECT_EQ(t2.size(), 3);
	EXPECT_TRUE(t2.contains(d.get_name()));
}


TEST(HashTable, At)
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

	EXPECT_EQ(t1.at(a.get_name()), a);
	EXPECT_EQ(t1.at(b.get_name()), b);
	EXPECT_THROW(t1.at(d.get_name()), std::exception);
}


/* -------------------- MAIN -------------------- */

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}