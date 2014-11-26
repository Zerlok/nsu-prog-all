#include "main.h"
#include <gtest/gtest.h>


/* -------------------- STUDENT CLASS TESTS -------------------- */

TEST(Input, ZeroInit)
{
	const int argc = 1;
	const char *argv[] = {
		"TEST"
	};

	EXPECT_NO_THROW(Game game(argc, argv));
}

TEST(Input, FlagInit)
{
	const int argc = 5;
	const char *argv[] = {
		"TEST",
		"-d"
		"-s", "10",
		"-c", "defaults",
		"-m", "compile.sh",
	};

	EXPECT_NO_THROW(Game game(argc, argv));
}

TEST(Input, ArgumentInit)
{
	const int argc = 6;
	const char *argv[] = {
		"TEST",
		"--mode=tournamet",
		"--configs=defaults",
		"--steps=10",
		"--matrix=compile.sh",
		"--help"
	};

	EXPECT_NO_THROW(Game game(argc, argv));
}

TEST(Input, InvalidInput)
{
	const int argc = 21;
	const char *argv[] = {
		"TEST",
		"--mode=",
		"-?",
		"*?&&!",
		"-&",
		"***",
		"-:",
		"aiug943 7b9=1059-9tu-0139",
		"----steps=181",
		"sucks--=666",
		"--configs=C:\\Win\\",
		"--sups=kak",
		"--:)(*^#@=)(@",
		"--mode=&&&&&&",
		"--configs=sssss",
		"--",
		"--&=5",
		"von--",
		"-=-",
		"--1^& -\10-8ghbq--",
		"--hlpme"
	};

	EXPECT_NO_THROW(Game game(argc, argv));	
}


TEST(Factory, Init)
{
	EXPECT_NO_THROW(StrategyFactory strategies);
}


/* -------------------- MAIN -------------------- */

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}