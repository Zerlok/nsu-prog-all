#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "datapackage.h"
#include "sender.h"
#include "receiver.h"


bool operator==(const std::string &s1, const std::string &s2)
{
	return (!(s1.compare(s2)));
}


TEST(DataPackage, Init)
{
	std::string s = "Data";
	ASSERT_NO_THROW
	({
		 DataPackage p0;
		 DataPackage p1 = DataPackage(s);
		 DataPackage p2 = DataPackage(p1);

		 EXPECT_EQ(p1, p2);
		 EXPECT_EQ(int(s.size()), p1.get_data_len());
	});
}


TEST(DataPackage, EmptyPackage)
{
	DataPackage p;

	EXPECT_EQ(0, p.get_data_len());
	EXPECT_EQ(0, p.get_crc());
	EXPECT_FALSE(p.is_valid());
}


TEST(DataPackage, SinglePackageTransmission)
{
	const std::vector<std::string> data = {
		"",
		"Hello, world!",
		"Some Data"
	};

	for (const std::string &d : data)
	{
		DataPackage sending_package = DataPackage(d);
		DataPackage receiving_package;

		std::stringstream ss;
		ss << sending_package;
		ss >> receiving_package;

		EXPECT_EQ(sending_package, receiving_package);
	}
}


TEST(Transmission, Simple)
{
	const std::string &message = "Hello, world! This is a simple message for data transmission test. And doubled (Hello, world! This is a simple message for data transmission test).";
	Sender s(message);
	Receiver r;

	DataPackage package;
	while (s.get_left_packages_num() > 0)
	{
		package = s.give_outgoing_package();
		EXPECT_TRUE(package.is_valid());
		r.take_incoming_package(package);

		package = r.give_outgoing_package();
		EXPECT_TRUE(package.is_valid());
		s.take_incoming_package(package);
	}

	EXPECT_EQ(Sender::Status::data_transmission_finished, s.get_status());
	EXPECT_EQ(Receiver::Status::data_transmission_finished, r.get_status());
	EXPECT_EQ(r.get_total_packages_num(), r.get_received_packages_num());
	EXPECT_EQ(message, r.get_data());
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
