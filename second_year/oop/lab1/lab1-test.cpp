#include "table.h"
#include <gtest/gtest.h>


// TEST(HashTableTest, Init)
// {
// 	HashTable a;
// 	Value row = a["Danil Troshnev"];

// 	EXPECT_EQ(row.age, 18);
// }


// /* For Hash : key.size() * key[0] */
// TEST(HashTableTest, ValuesAddressConst)
// {
// 	HashTable a;

// 	Value *row1 = &(a["Danil Troshnev"]);
// 	row1->age = 19;

// 	Value *row2 = &(a["Dima Vishnevyh"]); // Collision!
// 	Value *row3 = &(a["Danil Troshnev"]);
// 	Value *row4 = &(a["Ivan Ivanov"]);

// 	EXPECT_NE(row1, row2);
// 	EXPECT_NE(row2, row3);
// 	EXPECT_EQ(row1, row3);
// 	EXPECT_NE(row1, row4);

// 	EXPECT_EQ(row3->age, 19);
// }


// TEST(HashTableTest, CreateFromParent)
// {
// 	HashTable a;
// 	Value *row1 = &(a["Danil"]);
// 	row1->age = 19;

// 	HashTable b(a);
// 	Value *row2 = &(b["Danil"]);

// 	EXPECT_NE(row1, row2);
// 	EXPECT_EQ(row2->age, 19);
// }


/* -------------------- STUDENT CLASS TESTS -------------------- */

TEST(StudentTest, Init)
{
	Student a("Danil");
	Student b("Igor", 21, 3, 4.2, "Physics");
	
	EXPECT_EQ(a.get_age(), 18);
	EXPECT_NE(a, b);
}


TEST(StudentTest, Copy)
{
	Student a("Danil"), b(a);
	
	b.set_age(19);

	EXPECT_EQ(a.get_name(), b.get_name());
	EXPECT_NE(a.get_age(), b.get_age());
}


TEST(StudentTest, OperatorEQ)
{
	Student a("Danil");
	Student b("Igor");

	b = a;

	EXPECT_EQ(a.get_name(), b.get_name());
}


TEST(StudentTest, OperatorEQEQ)
{
	Student a("Danil");
	Student b(a);

	EXPECT_TRUE(a == b);
}


/* -------------------- ITEM CLASS TESTS -------------------- */

TEST(ItemTest, Init)
{
	Student a("Danil");
	Item item1("Danil", a), item2("Den"), item3(a);
	
	// item1.show();
	// item2.show();
	// item3.show();

	EXPECT_NE(item1, item2);
	EXPECT_NE(item2, item3);
	EXPECT_EQ(item1, item3);
}


TEST(ItemTest, Copy)
{
	Student a("Danil");
	Item item1(a), item2(item1);

	EXPECT_EQ(item1, item2);
}


TEST(ItemTest, OperatorEQ)
{
	Student a("Den"), b("Jeff");
	Item item1("Danil", a), item2("J", b);

	item2 = item1;

	EXPECT_EQ(item1, item2);
}


TEST(ItemTest, OperatorEQEQ)
{
	Student a("Danil"), b("Denis");
	Item item1("Danil", a), item2("Danil2", a), item3(b), item4(b);

	EXPECT_FALSE(item1 == item2);
	EXPECT_FALSE(item1 == item3);
	EXPECT_TRUE(item3 == item4);
}


TEST(ItemTest, Pushback)
{
	Student a("Danil"), b("Bob"), c("Monica");
	Item item1(a), item2(b), item3(c);

	// std::cout << "Inited...";

	item1.push_back(item2);
	item2.push_back(item3);

	// std::cout << "Pushed...";

	// item1.show();
	// item2.show();
	// item3.show();

	// EXPECT_EQ(item1.get_next(), item2);
	// EXPECT_EQ(item2.get_next(), item3);
}


TEST(ItemTest, Empty)
{
	Item item1("empty");

	item1.show();

	EXPECT_TRUE(item1.is_empty());
}


/* -------------------- MAIN -------------------- */

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}