#include <gtest/gtest.h>
#include "bigvector.h"


template<class T>
void fillvalue(const std::string& filename, const size_t& size, const T& value)
{
	std::ofstream ofs(filename, std::ios::out | std::ios::binary);

	serialize(ofs, size);
	for (size_t i = 0; i < size; ++i)
		serialize(ofs, value);

	ofs.close();
}


void fillfine(const std::string& filename, const size_t& size)
{
	std::ofstream ofs(filename, std::ios::out | std::ios::binary);

	serialize(ofs, size);
	for (size_t i = 0; i < size; ++i)
		serialize(ofs, i);

	ofs.close();
}


TEST(Serializer, UnsignedInteger)
{
	const size_t expected = 37373;
	std::ofstream ofs("test.ser", std::ios::out | std::ios::binary);
	serialize(ofs, expected);
	ofs.close();

	std::ifstream ifs("test.ser", std::ios::in | std::ios::binary);
	size_t actual;
	deserialize(ifs, actual);
	ifs.close();

	EXPECT_EQ(expected, actual);

	std::remove("test.ser");
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

	std::remove("test.ser");
}


TEST(BigVector, Init)
{
	const size_t size = 1000;
	const int val = 37;
	fillvalue("data.ser", size, val);

	BigVector<int> values("data.ser", 50);
	EXPECT_EQ(size, values.size());
	EXPECT_EQ(val, values[0]);
	EXPECT_EQ(val, values[size-1]);
}


TEST(BigVector, PushBack)
{
	const size_t width = 10;
	const size_t size = width*5;
	BigVector<int> values("data2.ser", width);

	for (size_t i = 0; i < size; ++i)
		values.push_back(i);

	EXPECT_EQ(size, values.size());

	for (size_t i = 0; i < size; ++i)
		EXPECT_EQ(i, values[i]);

	std::remove("data2.ser");
}


TEST(BigVector, Iterator)
{
	fillfine("test.ser", 1000);
	BigVector<int> values("test.ser", 100);
	BigVector<int>& vals = values;

	for (int& x : vals)
		x += 10;
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

