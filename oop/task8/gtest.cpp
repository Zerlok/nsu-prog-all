#include <gtest/gtest.h>

#include "affinetransformation.h"


TEST(AffineTransformation, Translation)
{
	TranslationTransformation tr1(5.0, -3.0);
	TranslationTransformation tr2(-5.0, 3.0);

	int x = -10;
	int y = 2;

	tr1.transform(x, y);
	EXPECT_EQ(-5, x);
	EXPECT_EQ(-1, y);

	tr2.transform(x, y);
	EXPECT_EQ(-10, x);
	EXPECT_EQ(2, y);
}


TEST(AffineTransformation, Rotation)
{
	RotationTransformation rot30(30);
	RotationTransformation rot180(180);

	double x = 0;
	double y = 0;

	rot30.transform(x, y);
	EXPECT_EQ(0, x);
	EXPECT_EQ(0, y);

	x = sqrt(3.0) * 100;
	y = -100;

	rot30.transform(x, y);
	EXPECT_EQ(200, round(x));
	EXPECT_EQ(0, round(y));

	x = 0;
	y = 10;

	rot180.transform(x, y);
	EXPECT_EQ(0, x);
	EXPECT_EQ(-10, y);
}


TEST(AffineTransformation, Scaling)
{
	ScalingTransformation sc(10, 10);

	int x = 1;
	int y = 3;

	sc.transform(x, y);
	EXPECT_EQ(10, x);
	EXPECT_EQ(30, y);
}


TEST(AffineTransformation, Complex)
{
	RotationTransformation aff(90);
	aff += TranslationTransformation(4, -5);

	int x = 5;
	int y = 4;

	aff.transform(x, y);
	EXPECT_EQ(0, x);
	EXPECT_EQ(0, y);
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
