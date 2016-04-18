#include <gtest/gtest.h>

#include "history.h"

#include "copycommand.h"
#include "helpcommand.h"
#include "insertcommand.h"
#include "redocommand.h"
#include "searchreplacecommand.h"
#include "setcommand.h"
#include "undocommand.h"


TEST(History, History)
{
	History hist;
	hist.push_back("1st");
	hist.push_back("2nd");
	hist.push_back("3rd");

	EXPECT_FALSE(hist.has_next());

	EXPECT_EQ("3rd", hist.get_current());
	EXPECT_EQ("2nd", hist.previous());
	EXPECT_EQ("1st", hist.previous());

	EXPECT_FALSE(hist.has_previous());

	EXPECT_EQ("2nd", hist.next());
	hist.push_back("4th");
	EXPECT_EQ("4th", hist.get_current());
	hist.push_back("5th");
	EXPECT_EQ("5th", hist.get_current());
}


TEST(Commands, CopyCommandExec)
{
	std::string buffer;
	const std::string data = "Hello, World!";

	CopyCommand copy_all;
	CopyCommand copy(7, -2);

	Command::Result res = copy_all.execute(data, buffer);
	EXPECT_EQ(data, buffer);

	res = copy.execute(data, buffer);
	EXPECT_TRUE(res);
	EXPECT_EQ("World", buffer);
}


TEST(Commands, InsertCommandExec)
{
	std::string buffer = ", World";
	const std::string data = "Hello!";

	InsertCommand from_buff_insert(-2);
	InsertCommand insert(0, "*** ");

	Command::Result res = from_buff_insert.execute(data, buffer);
	EXPECT_TRUE(res);
	EXPECT_EQ("Hello, World!", res.data);

	res = insert.execute(data, buffer);
	EXPECT_TRUE(res);
	EXPECT_EQ("*** Hello!", res.data);
}


TEST(Commands, SearchReplaceCommandExec)
{
	std::string buffer = "?";
	const std::string data = "Hello, World!";

	SearchReplaceCommand sed_buff("!");
	SearchReplaceCommand sed("l", "L");

	Command::Result res = sed_buff.execute(data, buffer);
	EXPECT_TRUE(res);
	EXPECT_EQ("Hello, World?", res.data);

	res = sed.execute(data, buffer);
	EXPECT_TRUE(res);
	EXPECT_EQ("HeLLo, WorLd!", res.data);
}


TEST(Commands, SetCommand)
{
	std::string buffer;
	const std::string data = "Hello!";
	const std::string new_data = "Welcome!";
	SetCommand set(new_data);

	Command::Result res = set.execute(data, buffer);
	EXPECT_TRUE(res);
	EXPECT_EQ(new_data, res.data);
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
