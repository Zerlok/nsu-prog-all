#include <gtest/gtest.h>
#include "bigvector.h"


TEST(Serializer, UnsignedInteger)
{
	const size_t expected = 33;
	std::fstream fs("test.ser", std::ios::in | std::ios::out | std::ios::binary);
	serialize(fs, expected);

	size_t actual;
	fs.seekp(0);
	deserialize(fs, actual);
	fs.close();

	EXPECT_EQ(expected, actual);
}


TEST(Serializer, Vector)
{
	const std::vector<int> expected = {1, 2, 3};
	std::ofstream ofs("test.ser", std::ios::out | std::ios::binary);
	serialize(ofs, expected);
	ofs.close();

	std::vector<int> actual;
	std::ifstream ifs("test.ser", std::ios::in | std::ios::binary);
	deserialize(ifs, actual);
	ifs.close();

	EXPECT_EQ(expected, actual);
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

