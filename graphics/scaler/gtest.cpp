#ifdef __GTEST__

#include <gtest/gtest.h>

#define EXPECT_CLOSE(val1, val2) EXPECT_NEAR(val1, val2, 0.0001f)


#include <grid.hpp>

static const Grid g5x5 = {5, 5, 1.0, 1.0, 0.0, 0.0};
using PosPair = std::pair<float, float>;


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
	EXPECT_TRUE(g5x5.hasInside(g5x5.begin()));
	EXPECT_FALSE(g5x5.hasInside(g5x5.end()));

	Grid g(0, 0);
	EXPECT_EQ(g.begin(), g.end());
	EXPECT_FALSE(g.hasInside(g.end()));

	size_t cntr = 0;
	for (Grid::iterator it = g5x5.begin();
		 it != g5x5.end();
		 ++it)
	{
		EXPECT_TRUE(g5x5.hasInside(it));
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
	const std::vector<PosPair> innerPositions = {
		{0.0, 0.0},
		{1.0, 0.0},
		{2.0, 0.0},
		{0.0, 1.0},
		{1.0, 1.0},
		{2.0, 1.0},
		{0.0, 2.0},
		{1.0, 2.0},
		{2.0, 2.0},
		{2.0, 0.0},
		{3.0, 0.0},
		{4.0, 0.0},
		{2.0, 1.0},
		{3.0, 1.0},
		{4.0, 1.0},
		{2.0, 2.0},
		{3.0, 2.0},
		{4.0, 2.0},
		{0.0, 2.0},
		{1.0, 2.0},
		{2.0, 2.0},
		{0.0, 3.0},
		{1.0, 3.0},
		{2.0, 3.0},
		{0.0, 4.0},
		{1.0, 4.0},
		{2.0, 4.0},
		{2.0, 2.0},
		{3.0, 2.0},
		{4.0, 2.0},
		{2.0, 3.0},
		{3.0, 3.0},
		{4.0, 3.0},
		{2.0, 4.0},
		{3.0, 4.0},
		{4.0, 4.0},
	};
	const std::vector<PosPair> innerGridOffsets = {
		{0.0, 0.0},
		{2.0, 0.0},
		{0.0, 2.0},
		{2.0, 2.0},
	};

	Grid g2x2(2, 2);
	OverlayIterator it = overlay(g2x2, g5x5);
	const Grid& inGrid = it.getInnerGrid();
	const Grid::iterator& in = it.getInner();

	EXPECT_CLOSE(2.5f, g2x2.getCell().width);
	EXPECT_CLOSE(2.5f, g2x2.getCell().height);

	for (size_t i = 0; i < cells.size(); ++i)
	{
		EXPECT_EQ(3, inGrid.getColumns());
		EXPECT_EQ(3, inGrid.getRows());
		EXPECT_EQ(innerGridOffsets[i / 9], std::make_pair(inGrid.getOffsetX(), inGrid.getOffsetY())) << i;
		EXPECT_EQ(innerPositions[i], std::make_pair(in.getX(), in.getY())) << i;

		EXPECT_EQ(cells[i], it.getCell()) << "Idx: " << i;
		++it;
	}

	EXPECT_TRUE(it.isInnerEnd());
	EXPECT_TRUE(it.isOutterEnd());
}


TEST(Overlay, g2x2_g4x4)
{
	const std::vector<Grid::Cell> cells = std::vector<Grid::Cell>(16, {1.0, 1.0});
	const std::vector<PosPair> innerPositions = {
		{0.0, 0.0},
		{1.0, 0.0},
		{0.0, 1.0},
		{1.0, 1.0},
		{2.0, 0.0},
		{3.0, 0.0},
		{2.0, 1.0},
		{3.0, 1.0},
		{0.0, 2.0},
		{1.0, 2.0},
		{0.0, 3.0},
		{1.0, 3.0},
		{2.0, 2.0},
		{3.0, 2.0},
		{2.0, 3.0},
		{3.0, 3.0},
	};
	const std::vector<PosPair> innerGridOffsets = {
		{0.0, 0.0},
		{2.0, 0.0},
		{0.0, 2.0},
		{2.0, 2.0},
	};

	Grid g2x2(2, 2);
	Grid g4x4(4, 4);
	OverlayIterator it = overlay(g2x2, g4x4);
	const Grid& inGrid = it.getInnerGrid();
	const Grid::iterator& in = it.getInner();

	EXPECT_CLOSE(2.0f, g2x2.getCell().width);
	EXPECT_CLOSE(2.0f, g2x2.getCell().height);

	for (size_t i = 0; i < cells.size(); ++i)
	{
		EXPECT_EQ(2, inGrid.getColumns());
		EXPECT_EQ(2, inGrid.getRows());
		EXPECT_EQ(innerGridOffsets[i / 4], std::make_pair(inGrid.getOffsetX(), inGrid.getOffsetY())) << i;
		EXPECT_EQ(innerPositions[i], std::make_pair(in.getX(), in.getY())) << i;

		EXPECT_EQ(cells[i], it.getCell()) << "Idx: " << i;
		++it;
	}

	EXPECT_TRUE(it.isInnerEnd());
	EXPECT_TRUE(it.isOutterEnd());
}


TEST(Overlay, g3x3_g4x4)
{
	const float f1o3 = 1.0 / 3.0;
	const float f2o3 = 2.0 / 3.0;

	const std::vector<Grid::Cell> cells = {
		{1.0, 1.0},
		{f1o3, 1.0},
		{1.0, f1o3},
		{f1o3, f1o3},

		{f2o3, 1.0},
		{f2o3, 1.0},
		{f2o3, f1o3},
		{f2o3, f1o3},

		{f1o3, 1.0},
		{1.0, 1.0},
		{f1o3, f1o3},
		{1.0, f1o3},

		{1.0, f2o3},
		{f1o3, f2o3},
		{1.0, f2o3},
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

		{f2o3, f1o3},
		{f2o3, f1o3},
		{f2o3, 1.0},
		{f2o3, 1.0},

		{f1o3, f1o3},
		{1.0, f1o3},
		{f1o3, 1.0},
		{1.0, 1.0},
	};
	const std::vector<PosPair> innerPositions = {
		{0.0, 0.0},
		{1.0, 0.0},
		{0.0, 1.0},
		{1.0, 1.0},
		{1.0, 0.0},
		{2.0, 0.0},
		{1.0, 1.0},
		{2.0, 1.0},
		{2.0, 0.0},
		{3.0, 0.0},
		{2.0, 1.0},
		{3.0, 1.0},
		{0.0, 1.0},
		{1.0, 1.0},
		{0.0, 2.0},
		{1.0, 2.0},
		{1.0, 1.0},
		{2.0, 1.0},
		{1.0, 2.0},
		{2.0, 2.0},
		{2.0, 1.0},
		{3.0, 1.0},
		{2.0, 2.0},
		{3.0, 2.0},
		{0.0, 2.0},
		{1.0, 2.0},
		{0.0, 3.0},
		{1.0, 3.0},
		{1.0, 2.0},
		{2.0, 2.0},
		{1.0, 3.0},
		{2.0, 3.0},
		{2.0, 2.0},
		{3.0, 2.0},
		{2.0, 3.0},
		{3.0, 3.0},
	};
	const std::vector<PosPair> innerGridOffsets = {
		{0.0, 0.0},
		{1.0, 0.0},
		{2.0, 0.0},
		{0.0, 1.0},
		{1.0, 1.0},
		{2.0, 1.0},
		{0.0, 2.0},
		{1.0, 2.0},
		{2.0, 2.0},
	};

	Grid g3x3(3, 3);
	Grid g4x4(4, 4);
	OverlayIterator it = overlay(g3x3, g4x4);
	const Grid& inGrid = it.getInnerGrid();
	const Grid::iterator& in = it.getInner();

	EXPECT_CLOSE(4.0 / 3.0, g3x3.getCell().width);
	EXPECT_CLOSE(4.0 / 3.0, g3x3.getCell().height);

	for (size_t i = 0; i < cells.size(); ++i)
	{
		EXPECT_EQ(2, inGrid.getColumns());
		EXPECT_EQ(2, inGrid.getRows());
		EXPECT_EQ(innerGridOffsets[i / 4], std::make_pair(inGrid.getOffsetX(), inGrid.getOffsetY())) << i;
		EXPECT_EQ(innerPositions[i], std::make_pair(in.getX(), in.getY())) << i;

		const Grid::Cell c = it.getCell();
		EXPECT_CLOSE(cells[i].width, c.width) << "Idx: " << i << ", actual: " << c << ", expected: " << cells[i];
		EXPECT_CLOSE(cells[i].height, c.height) << "Idx: " << i << ", actual: " << c << ", expected: " << cells[i];
		++it;
	}

	EXPECT_TRUE(it.isInnerEnd());
	EXPECT_TRUE(it.isOutterEnd());
}


TEST(Overlay, g8x8_g18x18)
{
	Grid g8x8(8, 8);
	Grid g18x18(18, 18);

	OverlayIterator it = overlay(g18x18, g8x8);

	size_t outterCntr = 0;
	size_t innerCntr = 0;
	for (Grid::iterator& out = it.getOutter(); !it.isOutterEnd(); ++it)
	{
		EXPECT_TRUE(g8x8.hasInside(out));
		EXPECT_TRUE(g18x18.hasInside(out));

		for (Grid::iterator& in = it.getInner(); !it.isInnerEnd(); ++in)
		{
			EXPECT_TRUE(g8x8.hasInside(in));
			EXPECT_TRUE(g18x18.hasInside(in));
			++innerCntr;
		}

		++outterCntr;
	}

	EXPECT_EQ(64, outterCntr);
	EXPECT_EQ(625, innerCntr);

	EXPECT_TRUE(it.isInnerEnd());
	EXPECT_TRUE(it.isOutterEnd());
}


TEST(Overlay, Iterator)
{
	Grid g1x3(1, 3, 3, 1);
	Grid g3x1(3, 1, 1, 3);
	const std::vector<Grid::Cell> cells = std::vector<Grid::Cell>(9, {1.0, 1.0});

	size_t outterCntr = 0;
	size_t innerCntr = 0;
	OverlayIterator it = overlay(g1x3, g3x1);
	const Grid::iterator& out = it.getOutter();
	const Grid& inGrid = it.getInnerGrid();

	EXPECT_EQ(0.0, inGrid.getOffsetX());
	EXPECT_EQ(0.0, inGrid.getOffsetY());
	EXPECT_NE(Grid::Cell::zero, inGrid.getCell());

	for (; !it.isOutterEnd(); ++it)
	{
		EXPECT_TRUE(g1x3.hasInside(out));
		EXPECT_TRUE(g3x1.hasInside(out));

		for (Grid::iterator& in = it.getInner(); !it.isInnerEnd(); ++in)
		{
			EXPECT_TRUE(g1x3.hasInside(in));
			EXPECT_TRUE(g3x1.hasInside(in));
			EXPECT_EQ(cells[innerCntr], it.getCell());
			++innerCntr;
		}

		++outterCntr;
		EXPECT_EQ(outterCntr, innerCntr / 3);
	}

	EXPECT_EQ(3, outterCntr);
	EXPECT_EQ(cells.size(), innerCntr);

//	EXPECT_FALSE(inGrid.hasInside(in));

//	EXPECT_FALSE(g1x3.hasInside(in));
//	EXPECT_FALSE(g3x1.hasInside(in));

	EXPECT_FALSE(g1x3.hasInside(out));
	EXPECT_FALSE(g3x1.hasInside(out));
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


#endif
