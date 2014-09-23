#include "table.h"
#include <gtest/gtest.h>


TEST(HashTableTest, Init)
{
	HashTable a;
	Value row = a["Danil Troshnev"];

	EXPECT_EQ(row.age, 18);
}


/* For Hash : key.size() * key[0] */
TEST(HashTableTest, ValuesAddressConst)
{
	HashTable a;

	Value *row1 = &(a["Danil Troshnev"]);
	row1->age = 19;

	Value *row2 = &(a["Dima Vishnevyh"]); // Collision!
	Value *row3 = &(a["Danil Troshnev"]);
	Value *row4 = &(a["Ivan Ivanov"]);

	EXPECT_NE(row1, row2);
	EXPECT_NE(row2, row3);
	EXPECT_EQ(row1, row3);
	EXPECT_NE(row1, row4);

	EXPECT_EQ(row3->age, 19);
}


TEST(HashTableTest, CreateFromParent)
{
	HashTable a;
	Value *row1 = &(a["Danil"]);
	row1->age = 19;

	HashTable b(a);
	Value *row2 = &(b["Danil"]);

	EXPECT_NE(row1, row2);
	EXPECT_EQ(row2->age, 19);
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}