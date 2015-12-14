#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "datapackage.h"


TEST(DataPackage, Init)
{
	std::string s = "Data";
	ASSERT_NO_THROW
	({
		 DataPackage p0;
		 DataPackage p1 = DataPackage(s);
		 DataPackage p2 = DataPackage(p1);

		 EXPECT_EQ(p1, p2);
		 EXPECT_EQ(s.size(), p1.get_size());
	});
}


TEST(DataPackage, EmptyPackage)
{
	DataPackage p;

	EXPECT_EQ(0, p.get_size());
	EXPECT_EQ(0, p.get_crc());
}


//TEST(DataPackage, PackageT)
//{
//	const std::vector<std::string> data = {
//		"",
//		"*",
//		"Some Data"
//	};

//	for (const std::string &d : data)
//	{
//		DataPackage sending_package = DataPackage(d);
//		DataPackage receiving_package;

//		std::stringstream ss;
//		ss << sending_package;
//		ss >> receiving_package;

//		EXPECT_EQ(sending_package, receiving_package);
//		EXPECT_EQ(sending_package.get_crc(), receiving_package.get_crc());
//	}
//}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
