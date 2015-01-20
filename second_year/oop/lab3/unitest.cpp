#include <gtest/gtest.h>

#include "main.h"
#include "strategy.h"
#include "factory.h"
#include "mode.h"
#include "game.h"

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


TEST(CrazyStrategy, Init)
{
	EXPECT_NO_THROW({
		CrazyStrategy strat;
	});
}


TEST(Factory, Init)
{
	EXPECT_NO_THROW({
		StrategyFactory strategies(NULL, "ololo");

		strategies.set_id<TrustfulStrategy>("trust");
		strategies.set_id<MistrustfulStrategy>("mistrust");
		strategies.set_id<CrazyStrategy>("crazy");

		std::string strat("trust");
		Strategy *my = strategies.get(strat);

		Keys skeys = strategies.get_all_registered();

		std::copy(
				skeys.begin(),
				skeys.end(),
				std::ostream_iterator<std::string>(std::cout, ", ")
		);

		// for (Keys::iterator item = skeys.begin(); item != skeys.end(); item++)
		// {
		// 	std::cout << (*item) << std::endl;
		// }
	});
}


/* -------------------- MAIN -------------------- */

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}