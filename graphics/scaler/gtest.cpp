#ifdef __GTEST__

#include <gtest/gtest.h>

#define EXPECT_CLOSE(val1, val2) EXPECT_NEAR(val1, val2, 0.0001f);


#include <grid.hpp>

static const Grid g5x5 = {5, 5};


TEST(Grid, LeftTop)
{
	EXPECT_EQ(Grid::Cell::zero, g5x5.getLeftTop(0.0, 0.0));
	EXPECT_EQ(Grid::Cell::zero, g5x5.getLeftTop(5.0, 0.0));
	EXPECT_EQ(Grid::Cell::zero, g5x5.getLeftTop(0.0, 5.0));

	EXPECT_EQ(Grid::Cell::normal, g5x5.getLeftTop(1.0, 1.0));
	EXPECT_EQ(Grid::Cell::normal, g5x5.getLeftTop(5.0, 5.0));
	EXPECT_EQ(Grid::Cell::zero, g5x5.getLeftTop(5.5, 5.5));

	const Grid::Cell cell(0.5, 0.5);
	EXPECT_EQ(cell, g5x5.getLeftTop(0.5, 0.5));
	EXPECT_EQ(cell, g5x5.getLeftTop(1.5, 1.5));
}


TEST(Grid, RightTop)
{
	EXPECT_EQ(Grid::Cell::zero, g5x5.getRightTop(0.0, 0.0));
	EXPECT_EQ(Grid::Cell::zero, g5x5.getRightTop(5.0, 0.0));
	EXPECT_EQ(Grid::Cell::zero, g5x5.getRightTop(5.0, 5.0));

	EXPECT_EQ(Grid::Cell::normal, g5x5.getRightTop(1.0, 1.0));
	EXPECT_EQ(Grid::Cell::normal, g5x5.getRightTop(0.0, 5.0));

	const Grid::Cell cell(0.5, 0.5);
	EXPECT_EQ(cell, g5x5.getRightTop(0.5, 0.5));
	EXPECT_EQ(cell, g5x5.getRightTop(1.5, 1.5));

	EXPECT_EQ(Grid::Cell::zero, g5x5.getRightTop(5.5, 5.5));
}


TEST(Grid, LeftBottom)
{
	EXPECT_EQ(Grid::Cell::zero, g5x5.getLeftBottom(0.0, 0.0));
	EXPECT_EQ(Grid::Cell::zero, g5x5.getLeftBottom(0.0, 5.0));
	EXPECT_EQ(Grid::Cell::zero, g5x5.getLeftBottom(5.0, 5.0));

	EXPECT_EQ(Grid::Cell::normal, g5x5.getLeftBottom(1.0, 1.0));
	EXPECT_EQ(Grid::Cell::normal, g5x5.getLeftBottom(5.0, 0.0));

	const Grid::Cell cell(0.5, 0.5);
	EXPECT_EQ(cell, g5x5.getLeftBottom(0.5, 0.5));
	EXPECT_EQ(cell, g5x5.getLeftBottom(1.5, 1.5));

	EXPECT_EQ(Grid::Cell::zero, g5x5.getLeftBottom(5.5, 5.5));
}


TEST(Grid, RightBottom)
{
	EXPECT_EQ(Grid::Cell::zero, g5x5.getRightBottom(5.0, 0.0));
	EXPECT_EQ(Grid::Cell::zero, g5x5.getRightBottom(0.0, 5.0));
	EXPECT_EQ(Grid::Cell::zero, g5x5.getRightBottom(5.0, 5.0));

	EXPECT_EQ(Grid::Cell::normal, g5x5.getRightBottom(1.0, 1.0));
	EXPECT_EQ(Grid::Cell::normal, g5x5.getRightBottom(0.0, 0.0));

	const Grid::Cell cell(0.5, 0.5);
	EXPECT_EQ(cell, g5x5.getRightBottom(0.5, 0.5));
	EXPECT_EQ(cell, g5x5.getRightBottom(1.5, 1.5));

	EXPECT_EQ(Grid::Cell::zero, g5x5.getRightBottom(5.5, 5.5));
}


TEST(Grid, Iterator)
{
	EXPECT_NE(g5x5.begin(), g5x5.end());

	Grid g(0, 0);
	EXPECT_EQ(g.begin(), g.end());

	size_t cntr = 0;
	for (Grid::iterator it = g5x5.begin();
		 it != g5x5.end();
		 ++it)
	{
		EXPECT_EQ(Grid::Cell::normal, it.getCell());
		++cntr;
	}

	EXPECT_EQ(g5x5.getColumns() * g5x5.getRows(), cntr);
}


TEST(Grid, CellResizeWhenOverlaying)
{
	Grid g2x2(2, 2);
	EXPECT_EQ(Grid::Cell::normal, g2x2.getCell());

	g2x2.resizeCellsToOverlay(g5x5);

	const Grid::Cell cell(2.5, 2.5);
	EXPECT_EQ(cell, g2x2.getCell());

	const Grid g2(2, 2, 2.0, 2.0);
	g2x2.resizeCellsToOverlay(g2);
	EXPECT_EQ(g2.getCell(), g2x2.getCell());
}


TEST(Grid, Overlay)
{
	const std::vector<Grid::Cell> cells = {
		{1.0, 1.0}, {1.0, 1.0}, {0.5, 1.0},
		{1.0, 1.0}, {1.0, 1.0}, {0.5, 1.0},
		{1.0, 0.5}, {1.0, 0.5}, {0.5, 0.5},

		{0.5, 1.0}, {1.0, 1.0}, {1.0, 1.0},
		{0.5, 1.0}, {1.0, 1.0}, {1.0, 1.0},
		{0.5, 0.5}, {1.0, 0.5}, {1.0, 0.5},

		{1.0, 0.5}, {1.0, 0.5}, {0.5, 0.5},
		{1.0, 1.0}, {1.0, 1.0}, {0.5, 1.0},
		{1.0, 1.0}, {1.0, 1.0}, {0.5, 1.0},

		{0.5, 0.5}, {1.0, 0.5}, {1.0, 0.5},
		{0.5, 1.0}, {1.0, 1.0}, {1.0, 1.0},
		{0.5, 1.0}, {1.0, 1.0}, {1.0, 1.0},
	};

	Grid g2x2(2, 2);
	EXPECT_EQ(Grid::Cell::normal, g2x2.getCell());

	Grid::LayingIterator it = g2x2.overlay(g5x5);
	for (size_t i = 0; i < cells.size(); ++i)
	{
		EXPECT_EQ(cells[i], it.getCell()) << "Idx: " << i;
//		std::cout << i << ": " << it.getCell() << std::endl;
		++it;
	}
}



int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


#endif
