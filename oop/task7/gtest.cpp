#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <vector>

#include "datapackage.h"
#include "sender.h"
#include "receiver.h"
#include "media.h"
#include "xprotocol.h"


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


TEST(Transferring, Manual)
{
	const std::string &message = xmodem_utils::read_all_input("normal-media-test.txt");
	Sender s(message);
	Receiver r;

	DataPackage package;
	while (!s.is_stopped())
	{
		package = r.give_outgoing_package();
		EXPECT_TRUE(package.is_valid());
		s.take_incoming_package(package);

		package = s.give_outgoing_package();
		EXPECT_TRUE(package.is_valid());
		r.take_incoming_package(package);
	}

	EXPECT_EQ(Sender::Status::data_transmission_finished, s.get_status()) << package;
	EXPECT_EQ(Receiver::Status::data_transmission_finished, r.get_status()) << package;
	EXPECT_EQ(r.get_total_packages_num(), r.get_received_packages_num()) << package;
	EXPECT_EQ(message, r.get_received_data()) << package;
}


TEST(Transferring, NormalMedia)
{
	const std::string &message = xmodem_utils::read_all_input("normal-media-test.txt");
	Sender s(message);
	Receiver r;
	NormalMedia media(s, r);

	EXPECT_TRUE(media.simulate_transmission());
	EXPECT_TRUE(s.is_stopped()) << s.give_outgoing_package() << " " << s.get_status();
	EXPECT_TRUE(r.is_stopped()) << r.give_outgoing_package() << " " << r.get_status();
}


TEST(Transferring, BitFailingMedia)
{
	const std::string &message = xmodem_utils::read_all_input("normal-media-test.txt");
	Sender s(message);
	Receiver r;
	BitFailingMedia media(s, r);

	EXPECT_TRUE(media.simulate_transmission());
	EXPECT_TRUE(s.is_stopped()) << s.give_outgoing_package() << " " << s.get_status();
	EXPECT_TRUE(r.is_stopped()) << r.give_outgoing_package() << " " << r.get_status();
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
