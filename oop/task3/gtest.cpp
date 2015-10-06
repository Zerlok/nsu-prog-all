#include <iostream>

#include <gtest/gtest.h>
#include "date.h"


TEST(SimpleTest, SimpleTests)
{
	ASSERT_EQ(4, 2+2);
}


TEST(DateTestBranch, DateInit)
{
	ASSERT_NO_THROW({ Date today; });

	ASSERT_THROW(
	{
		Date invalid(2000, 13, 1);
	}, std::invalid_argument);

	ASSERT_THROW(
	{
		Date invalid(2000, 2, 30);
	}, std::invalid_argument);
}


TEST(DateTestBranch, LeapYear)
{
	Date leap1(2000, 1, 1);
	Date leap2(1996, 1, 1);
	Date leap3(2004, 1, 1);
	Date leap4(1600, 1, 1);
	Date normal1(2001, 1, 1);
	Date normal2(1900, 1, 1);
	Date normal3(1995, 1, 1);
	Date normal4(1800, 1, 1);

	EXPECT_TRUE(leap1.is_leap_year());
	EXPECT_TRUE(leap2.is_leap_year());
	EXPECT_TRUE(leap3.is_leap_year());
	EXPECT_TRUE(leap4.is_leap_year());
	EXPECT_FALSE(normal1.is_leap_year());
	EXPECT_FALSE(normal2.is_leap_year());
	EXPECT_FALSE(normal3.is_leap_year());
	EXPECT_FALSE(normal4 .is_leap_year());
}


TEST(DateTestBranch, DaysCounting)
{
	Date d1(1, 1, 1);
	Date d2(1, 1, 2);
	Date d3(1, 2, 1);
	Date d4(2, 1, 1);
	Date d5(2, 2, 2);
	Date d6(1000, 1, 1);
	Date d7(2000, 1, 1);

	EXPECT_EQ(0, d1.to_days());
	EXPECT_EQ(1, d2.to_days());
	EXPECT_EQ(31, d3.to_days());
	EXPECT_EQ(365, d4.to_days());
	EXPECT_EQ(397, d5.to_days());

	EXPECT_EQ(364877, d6.to_days());
	EXPECT_EQ(730119, d7.to_days());
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

