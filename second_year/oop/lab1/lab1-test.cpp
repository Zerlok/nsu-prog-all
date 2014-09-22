#include "table.h"
#include <gtest/gtest.h>


// TEST(HashTableTest, ConstrDestr)
// {
// 	HashTable a;
// }


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

	Value *row2 = &(a["Dima Vishnevyh"]);
	Value *row3 = &(a["Danil Troshnev"]);

	EXPECT_NE(row1, row2);
	EXPECT_NE(row2, row3);
	EXPECT_EQ(row1, row3);

	EXPECT_EQ(row1->age, row3->age);
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}