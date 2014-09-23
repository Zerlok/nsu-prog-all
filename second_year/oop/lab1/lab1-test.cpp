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


TEST(ItemTest, Init)
{
	Student a("Danil");
	Item i("Danil", a);
}


TEST(ItemTest, Copy)
{
	Student a("Danil");
	Item item1("Danil", a), item2(item1);

	EXPECT_EQ(item1, item2);
}


TEST(ItemTest, OperatorEQ)
{
	Student a("Den");
	Item item1("Danil", a), item2("den", a);

	item2 = item1;

	EXPECT_EQ(item1, item2);
}


TEST(ItemTest, OperatorEQEQ)
{
	Student a("Danil"), b("Denis");
	Item item1("Danil", a), item2("Danil2", a), item3("Denis", b), item4("Denis", b);

	EXPECT_FALSE(item1 == item2);
	EXPECT_FALSE(item1 == item3);
	EXPECT_TRUE(item3 == item4);
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}