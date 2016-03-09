#include <gtest/gtest.h>
#include "bigvector.h"


template<class T>
void fillfile(const std::string& filename, const size_t& size, const T& value)
{
	std::ofstream ofs(filename, std::ios::out | std::ios::binary);

	serialize(ofs, size);
	for (size_t i = 0; i < size; ++i)
		serialize(ofs, value);

	ofs.close();
}


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


TEST(BigVector, Init)
{
	const size_t size = 1000;
	const int val = 37;
	fillfile("data.ser", size, val);

	BigVector<int> values("data.ser", 50);
	EXPECT_EQ(size, values.size());
	EXPECT_EQ(val, values[0]);
	EXPECT_EQ(val, values[size-1]);
}


TEST(BigVector, PushBack)
{
	BigVector<int> values("data.ser", 10);
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

