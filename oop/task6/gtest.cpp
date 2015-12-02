#include <gtest/gtest.h>

#include "point.h"
#include "lifeobject.h"
#include "populationmap.h"


std::ostream &operator<<(std::ostream &out, const std::vector<Point> &points)
{
	for (const Point &p : points)
		out << p << " ";
	return out;
}


TEST(Point, Comparing)
{
	Point p1(0, 0);
	Point p2(1, 1);
	Point p3(0, 5);
	Point p4(1, 5);
	Point p5(10, 10);

	EXPECT_EQ(Point::zero, p1);
	EXPECT_NE(p1, p3);
	EXPECT_NE(p1, p2);

	EXPECT_LT(p1, p2);
	EXPECT_LT(p3, p5);

	EXPECT_LE(p1, p3);
	EXPECT_LE(p2, p4);

	EXPECT_GT(p2, p1);
	EXPECT_GT(p5, p3);

	EXPECT_GE(p3, p1);
	EXPECT_GE(p4, p2);
}


TEST(PopulationMap, IsValidPosition)
{
	PopulationMap map({10, 10});
	std::vector<Point> valid_positions = {
		{0, 0},
		{0, 1},
		{1, 1},
		{1, 0},
		{9, 9},
		{9, 4},
		{5, 9},
		{5, 5}
	};
	std::vector<Point> invalid_positions = {
		{10, 10},
		{-1, 4},
		{4, -1},
		{-1, -1},
		{10, 5},
		{5, 10}
	};

	for (const Point &pos : valid_positions)
		EXPECT_TRUE(map.is_valid_position(pos)) << pos;

	for (const Point &pos : invalid_positions)
		EXPECT_FALSE(map.is_valid_position(pos)) << pos;
}


TEST(PopulationMap, FreePositions)
{
	PopulationMap map(Point(10, 10));

	std::vector<Point> points = {
		{0, 0},
		{10, 10},
		{5, 5},
		{1, 1},
		{0, 4},
		{9, 5}
	};
	std::vector<int> positions_num = {
		4,
		0,
		9,
		9,
		6,
		6
	};

	for (size_t i = 0; i < positions_num.size(); ++i)
	{
		std::vector<Point> free_positions = map.get_free_positions(points[i]);
		EXPECT_EQ(positions_num[i], free_positions.size()) << points[i] << " : " << free_positions;
	}
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
