#include <gtest/gtest.h>

#include "main.h"
#include "lifeform.h"
#include "universe.h"


TEST(Gtest, Init)
{
	ASSERT_EQ(4, 2 + 2);
	EXPECT_NE(0, 1);
}


TEST(Lifeform, Init)
{
	EXPECT_NO_THROW({
		Lifeform cell1;
		Lifeform cell2(DEAD);
		Lifeform cell3(ALIVE);
		Lifeform cell4(ALIVE);
	});
}


TEST(Lifeform, Is_Alive)
{
	Lifeform cell1;
	Lifeform cell2(DEAD);
	Lifeform cell3(ALIVE);
	Lifeform cell4(ALIVE);

	EXPECT_FALSE(cell1.is_alive());
	EXPECT_FALSE(cell2.is_alive());
	EXPECT_TRUE(cell3.is_alive());
	EXPECT_TRUE(cell4.is_alive());
}


TEST(Lifeform, BornKill)
{
	Lifeform cell1;
	Lifeform cell2(DEAD);
	Lifeform cell3(ALIVE);
	Lifeform cell4(ALIVE);

	EXPECT_TRUE(cell1.born());
	EXPECT_FALSE(cell2.kill());
	EXPECT_FALSE(cell3.born());
	EXPECT_TRUE(cell4.kill());

	EXPECT_TRUE(cell1.is_alive());
	EXPECT_FALSE(cell2.is_alive());
	EXPECT_TRUE(cell3.is_alive());
	EXPECT_FALSE(cell4.is_alive());
}


TEST(Lifeform, Addition)
{
	Lifeform cell1;
	Lifeform cell2(DEAD);
	Lifeform cell3(ALIVE);
	Lifeform cell4(ALIVE);

	EXPECT_EQ(2, cell1 + cell2 + cell3 + cell4);
	EXPECT_EQ(0, cell1 + cell2);
	EXPECT_EQ(2, cell3 + cell4);
	EXPECT_EQ(cell1 + cell3, cell2 + cell4);

	cell2.born();

	EXPECT_EQ(3, cell1 + cell2 + cell3 + cell4);
	EXPECT_EQ(1, cell1 + cell2);
	EXPECT_EQ(2, cell3 + cell4);

	cell4.kill();

	EXPECT_EQ(2, cell1 + cell2 + cell3 + cell4);
	EXPECT_EQ(1, cell1 + cell2);
	EXPECT_EQ(1, cell3 + cell4);
	EXPECT_EQ(cell1 + cell3, cell2 + cell4);
}


TEST(Lifeform, Statements)
{
	Lifeform cell1;
	Lifeform cell2;

	const bool new_state1[9] = {false, false, false, true, false, false, false, false, false};
	const bool new_state2[9] = {false, false, true, true, false, false, false, false, false};;

	for (int i = 0; i < 9; i++)
	{
		cell1 = DEAD;
		cell1.set_neighbours_num(i);
		cell1.apply_state_by_criteria(
				STD_BORN_CRITERIA,
				STD_SURVIVAL_CRITERIA);

		cell2 = ALIVE;
		cell2.set_neighbours_num(i);
		cell2.apply_state_by_criteria(
			STD_BORN_CRITERIA,
			STD_SURVIVAL_CRITERIA);

		EXPECT_EQ(new_state1[i], cell1.is_alive())
				<< (cell1.is_alive() ? "Alive" : "Dead")
				<< " cell (" << i << " neighbours)";

		EXPECT_EQ(new_state2[i], cell2.is_alive())
				<< (cell1.is_alive() ? "Alive" : "Dead")
				<< " cell (" << i << " neighbours)";
	}
}


TEST(Lifeform, EqOperator)
{
	Lifeform cell1;
	Lifeform cell2(DEAD);
	Lifeform cell3(ALIVE);
	Lifeform cell4(ALIVE);

	cell1 = ALIVE;
	cell2 = DEAD;
	cell3 = ALIVE;
	cell4 = DEAD;

	EXPECT_TRUE(cell1.is_alive());
	EXPECT_FALSE(cell2.is_alive());
	EXPECT_TRUE(cell3.is_alive());
	EXPECT_FALSE(cell4.is_alive());
}


TEST(Universe, Init)
{
	EXPECT_NO_THROW({
		Universe U(
				10,
				STD_BORN_CRITERIA,
				STD_SURVIVAL_CRITERIA);

		for (int x = 0; x < 10; x++)
			for (int y = 0; y < 10; y++)
			{
				EXPECT_FALSE(U.get(x, y).is_alive());
				EXPECT_EQ(0, U.count_neighbours(x, y));
			}
	});
}


TEST(Universe, StepDoing)
{
	Universe U(
		10,
		STD_BORN_CRITERIA,
		STD_SURVIVAL_CRITERIA);

	// The square
	U.init(3, 3);
	U.init(3, 4);
	U.init(4, 3, ALIVE);
	U.init(4, 4, ALIVE);

	// The blinker
	U.init(6, 7);
	U.init(7, 7, ALIVE);
	U.init(8, 7, ALIVE);

	// The alone cell
	U.init(1, 1);

	// The dead cell
	U.init(9, 9);
	U.init(9, 9, DEAD);
	U.init(8, 1, DEAD);

	const bool states_before[10][10] = {
		{false, false, false, false, false, false, false, false, false, false},
		{false, true, false, false, false, false, false, false, false, false},
		{false, false, false, false, false, false, false, false, false, false},
		{false, false, false, true, true, false, false, false, false, false},
		{false, false, false, true, true, false, false, false, false, false},
		{false, false, false, false, false, false, false, false, false, false},
		{false, false, false, false, false, false, false, true, false, false},
		{false, false, false, false, false, false, false, true, false, false},
		{false, false, false, false, false, false, false, true, false, false},
		{false, false, false, false, false, false, false, false, false, false}
	};

	const int neighbours[10][10] = {
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 2, 2, 2, 1, 0, 0, 0, 0},
		{0, 0, 2, 3, 3, 2, 0, 0, 0, 0},
		{0, 0, 2, 3, 3, 2, 0, 0, 0, 0},
		{0, 0, 1, 2, 2, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 2, 1, 2, 0},
		{0, 0, 0, 0, 0, 0, 3, 2, 3, 0},
		{0, 0, 0, 0, 0, 0, 2, 1, 2, 0},
		{0, 0, 0, 0, 0, 0, 1, 1, 1, 0}
	};

	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 10; y++)
		{
			EXPECT_EQ(states_before[x][y], U.get(x, y).is_alive()) << "cell (" << x << ", " << y << ")";
			EXPECT_EQ(neighbours[x][y], U.count_neighbours(x, y)) << "cell (" << x << ", " << y << ")";
		}

	std::cout << "Before:" << std::endl;
	U.draw();

	U.do_step();

	std::cout << "After:" << std::endl;
	U.draw();

	const bool states_after[10][10] = {
		{false, false, false, false, false, false, false, false, false, false},
		{false, false, false, false, false, false, false, false, false, false},
		{false, false, false, false, false, false, false, false, false, false},
		{false, false, false, true, true, false, false, false, false, false},
		{false, false, false, true, true, false, false, false, false, false},
		{false, false, false, false, false, false, false, false, false, false},
		{false, false, false, false, false, false, false, false, false, false},
		{false, false, false, false, false, false, true, true, true, false},
		{false, false, false, false, false, false, false, false, false, false},
		{false, false, false, false, false, false, false, false, false, false}
	};

	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 10; y++)
			EXPECT_EQ(states_after[x][y], U.get(x, y).is_alive()) << "cell (" << x << ", " << y << ")";
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}