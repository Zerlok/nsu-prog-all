#ifdef __GTEST__

#include <gtest/gtest.h>

#define EXPECT_CLOSE(val1, val2) EXPECT_NEAR(val1, val2, 0.001f)


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


TEST(Overlay, g2x2_g5x5)
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
	OverlayIterator it = overlay(g2x2, g5x5);

	Grid::iterator& in = it.getInner();
	Grid::iterator& out = it.getOutter();

	for (size_t i = 0; i < cells.size(); ++i)
	{
		EXPECT_EQ(cells[i], it.getCell()) << "Idx: " << i;
		++it;
	}

	EXPECT_EQ(it.getInnerEnd(), in);
	EXPECT_EQ(it.getOutterEnd(), out);
}


TEST(Overlay, g2x2_g4x4)
{
	const std::vector<Grid::Cell> cells = std::vector<Grid::Cell>(16, {1.0, 1.0});

	Grid g2x2(2, 2);
	Grid g4x4(4, 4);
	OverlayIterator it = overlay(g2x2, g4x4);

	Grid::iterator& in = it.getInner();
	Grid::iterator& out = it.getOutter();

	for (size_t i = 0; i < cells.size(); ++i)
	{
		EXPECT_EQ(cells[i], it.getCell()) << "Idx: " << i;
		++it;
	}

	EXPECT_EQ(it.getInnerEnd(), in);
	EXPECT_EQ(it.getOutterEnd(), out);
}


TEST(Overlay, g3x3_g4x4)
{
	const float f1o3 = 1.0 / 3.0;
	const float f2o3 = 2 * f1o3;

	const std::vector<Grid::Cell> cells = {
		{1.0, 1.0},
		{f1o3, 1.0},
		{1.0, f1o3},
		{f1o3, f1o3},

		{f2o3, 1.0},
		{f2o3, 1.0},
		{f2o3, f1o3},
		{f2o3, f1o3},

		{1.0, f1o3},
		{1.0, 1.0},
		{f1o3, f1o3},
		{f1o3, 1.0},

		{1.0, f2o3},
		{1.0, f2o3},
		{f1o3, f2o3},
		{f1o3, f2o3},

		{f2o3, f2o3},
		{f2o3, f2o3},
		{f2o3, f2o3},
		{f2o3, f2o3},

		{f1o3, f2o3},
		{1.0, f2o3},
		{f1o3, f2o3},
		{1.0, f2o3},

		{1.0, f1o3},
		{f1o3, f1o3},
		{1.0, 1.0},
		{f1o3, 1.0},

		{f1o3, f2o3},
		{f1o3, f2o3},
		{1.0, f2o3},
		{1.0, f2o3},

		{f1o3, f1o3},
		{1.0, f1o3},
		{f1o3, 1.0},
		{1.0, 1.0},
	};

	Grid g3x3(3, 3);
	Grid g4x4(4, 4);
	OverlayIterator it = overlay(g3x3, g4x4);

	Grid::iterator& in = it.getInner();
	Grid::iterator& out = it.getOutter();

	for (size_t i = 0; i < cells.size(); ++i)
	{
		const Grid::Cell c = it.getCell();
		EXPECT_CLOSE(cells[i].width, c.width) << i;
		EXPECT_CLOSE(cells[i].height, c.height) << i;
		++it;
	}

	EXPECT_EQ(it.getInnerEnd(), in);
	EXPECT_EQ(it.getOutterEnd(), out);
}


TEST(Overlay, Iterator)
{
	Grid g1x3(1, 3, 3, 1);
	Grid g3x1(3, 1, 1, 3);
	const std::vector<Grid::Cell> cells = std::vector<Grid::Cell>(9, {1.0, 1.0});

	size_t idx = 0;
	OverlayIterator it = overlay(g1x3, g3x1);
	for (Grid::iterator& o = it.getOutter(); o != it.getOutterEnd(); ++it)
	{
		for (Grid::iterator& i = it.getInner(); i != it.getInnerEnd(); ++it)
		{
			EXPECT_EQ(cells[idx], it.getCell()) << "Idx: " << idx;
			++idx;
		}

		EXPECT_EQ(0, idx % 3);
	}

	EXPECT_EQ(cells.size(), idx);
}




int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


#endif
