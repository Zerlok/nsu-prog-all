#include <iostream>
#include <gtest/gtest.h>

#include "date.h"
#include "week.h"
#include "calendar.h"


bool compare_dates(const Date &d1, const Date &d2)
{
	if ((d1.get_day() == d2.get_day())
			&& (d1.get_month() == d2.get_month())
			&& d1.get_year() == d2.get_year())
		return true;

	std::cout << "[Dates !=] " << d1 << " " << d2 << std::endl;
	return false;
}


TEST(Date, Init)
{
	ASSERT_NO_THROW({
			Date today;
			std::cout << "Today is : "
					<< today.get_month_name().substr(0, 3) << " "
					<< today.get_weekday_name().substr(0, 3) << " "
					<< today << std::endl;
	});

	ASSERT_THROW({ Date invalid(2000, 13, 1); }, std::invalid_argument);
	ASSERT_THROW({ Date invalid(2000, 2, 30); }, std::invalid_argument);
}


TEST(Date, LeapYear)
{
	const int leaps_num = 4;
	Date leaps[leaps_num] = {
		Date(2000, 1, 1),
		Date(1996, 1, 1),
		Date(2004, 1, 1),
		Date(1600, 1, 1)
	};
	const int normals_num = 6;
	Date normals[normals_num] = {
		Date(2001, 1, 1),
		Date(1900, 1, 1),
		Date(1995, 1, 1),
		Date(1800, 1, 1),
		Date(2100, 1, 1),
		Date(1997, 1, 1)
	};

	for (int i = 0; i < leaps_num; i++)
		EXPECT_TRUE(leaps[i].is_leap_year()) << leaps[i];

	for (int i = 0; i < normals_num; i++)
		EXPECT_FALSE(normals[i].is_leap_year()) << normals[i];
}


TEST(Date, DaysCounting)
{
	Date d1(1, 1, 1);
	Date d2(1, 1, 2);
	Date d3(1, 2, 1);
	Date d4(2, 1, 1);
	Date d5(2, 2, 2);

	EXPECT_EQ(0, d1.to_days());
	EXPECT_EQ(1, d2.to_days());
	EXPECT_EQ(31, d3.to_days());
	EXPECT_EQ(365, d4.to_days());
	EXPECT_EQ(397, d5.to_days());

	// Compared with python datetime package.
	Date d6(1000, 1, 1);
	Date d7(1995, 3, 1);
	Date d8(2000, 1, 1);
	Date d9(2015, 10, 6);

	EXPECT_EQ(7524, d9 - d7);
	EXPECT_EQ(364877, d6.to_days());
	EXPECT_EQ(730119, d8.to_days());
	EXPECT_EQ(735876, d9.to_days());
}


TEST(Date, ComparingOperators)
{
	Date d1(1, 1, 1);
	Date d10 = d1;
	Date d100(d1);

	Date d2(1, 1, 2);
	Date d3(1, 2, 1);
	Date d4(2, 1, 1);

	EXPECT_EQ(d1, Date(1, 1, 1));
	EXPECT_EQ(d1, d10);
	EXPECT_EQ(d1, d100);
	EXPECT_EQ(d10, d100);

	EXPECT_NE(d1, d2);
	EXPECT_GT(d2, d1);
	EXPECT_LT(d1, d2);

	EXPECT_LT(d1, d3);
	EXPECT_GT(d3, d2);
	EXPECT_LT(d2, d4);
	EXPECT_GT(d4, d3);

	Date d5(2000, 10, 20);
	Date d6(2005, 10, 1);
	Date d7(2000, 12, 1);

	EXPECT_GT(d6, d5);
	EXPECT_GT(d7, d5);
}


TEST(Date, IncrementOperator)
{
	const int len = 4;
	Date a[len] = {
		Date(1, 1, 1),
		Date(1, 1, 31),
		Date(1, 12, 31),
		Date(1999, 12, 31)
	};
	Date b[len] = {
		Date(1, 1, 2),
		Date(1, 2, 1),
		Date(2, 1, 1),
		Date(2000, 1, 1)
	};

	for (int i = 0; i < len; i++)
	{
		ASSERT_EQ(1, b[i]-a[i]) << b[i] << " - " << a[i] << " != 1 day.";
		EXPECT_EQ(b[i], a[i]++);
	}
}


TEST(Date, DecrementOperator)
{
	const int len = 4;
	Date a[len] = {
		Date(1, 1, 1),
		Date(1, 1, 31),
		Date(1, 12, 31),
		Date(1999, 12, 31)
	};
	Date b[len] = {
		Date(1, 1, 2),
		Date(1, 2, 1),
		Date(2, 1, 1),
		Date(2000, 1, 1)
	};

	for (int i = 0; i < len; i++)
	{
		ASSERT_EQ(1, b[i]-a[i]) << b[i] << " - " << a[i] << " != 1 day.";
		EXPECT_EQ(a[i], b[i]--);
	}
}


TEST(Date, PlusOperator)
{
	int diff;
	const int len = 6;

	Date a[len] = {
		Date(1, 1, 1),
		Date(1, 2, 2),
		Date(1, 12, 12),
		Date(1996, 2, 20),
		Date(1999, 12, 21),
		Date(1995, 3, 1)
	};
	Date b[len] = {
		Date(1, 1, 11),
		Date(1, 3, 3),
		Date(2, 1, 12),
		Date(1996, 3, 1),
		Date(2000, 1, 12),
		Date()
	};

	Date r;
	for (int i = 0; i < len; i++)
	{
		diff = b[i] - a[i];
		r = a[i] + diff;
		EXPECT_EQ(b[i], r) << b[i] << " != " << r << " diff: " << diff;
		EXPECT_TRUE(compare_dates(b[i], r));
	}
}


TEST(Date, MinusOperator)
{
	int diff;
	const int len = 6;

	Date a[len] = {
		Date(1, 1, 1),
		Date(1, 2, 2),
		Date(1, 12, 12),
		Date(1996, 2, 20),
		Date(1999, 12, 21),
		Date(1995, 3, 1)
	};
	Date b[len] = {
		Date(1, 1, 11),
		Date(1, 3, 3),
		Date(2, 1, 12),
		Date(1996, 3, 1),
		Date(2000, 1, 12),
		Date()
	};

	Date r;
	for (int i = 0; i < len; i++)
	{
		diff = b[i] - a[i];
		r = b[i] - diff;
		EXPECT_EQ(a[i], r) << a[i] << " != " << r << " diff: " << diff;
		EXPECT_TRUE(compare_dates(a[i], r));
	}
}


TEST(Week, Init)
{
	Date d1(1, 1, 1);
	Date d2(1, 2, 1);
	Date d3(1, 1, 8);

	ASSERT_NO_THROW({
		Week w1(d1);
		Week w2(d2);
		Week w3(d3);
	});

	Date inv1(1, 1, 2);
	Date inv2(1, 2, 2);
	Date inv3(1, 1, 7);

	ASSERT_THROW({ Week w(inv1); }, std::invalid_argument);
	ASSERT_THROW({ Week w(inv2); }, std::invalid_argument);
	ASSERT_THROW({ Week w(inv3); }, std::invalid_argument);
}


TEST(Calendar, Init)
{
	ASSERT_NO_THROW({
		Calendar c1(1);
		Calendar c2(2000);
	});
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

