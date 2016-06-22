#ifdef _DEBUG_

#include <gtest/gtest.h>

#include "haar.h"
#include "daub4.h"
#include "transformators.h"
#include "utils.h"
#include "gtest_utils.h"


using uchar = unsigned short;
using uchars = std::vector<uchar>;
using doubles = std::vector<double>;
using haardouble = HaarTransformation<double>;
using daub4double = DAUB4Transformation<double>;


static const doubles data {0, 0, 0, 0, 1, 1, 1, 2, 2, 1, 1, 1, 0, 0, 0, 0};
static const size_t len = data.size();


TEST(Utils, get_k_min_abs_value)
{
	const std::vector<int> ints {-10, 9, -8, 7, -6, 5, -4, 3, -2, 1};
	const std::vector<int> empty;

	EXPECT_EQ(0, get_k_min_abs_value(empty, 10));

	EXPECT_EQ(0, get_k_min_abs_value(ints, 0));
	EXPECT_EQ(1, get_k_min_abs_value(ints, 1));
	EXPECT_EQ(6, get_k_min_abs_value(ints, 6));
}


TEST(HaarTransformation, EncodeDecode)
{
	static const doubles encoded { 0, 0, 1, 1.5, 1.5, 1, 0, 0, 0, 0, 0, -0.5, 0.5, 0, 0, 0 };
	haardouble tr;

	doubles tmp = tr.forward(data, len);
	EXPECT_EQ(encoded, tmp);

	tmp = tr.backward(tmp, len);
	EXPECT_EQ(data, tmp);
}


TEST(DAUB4, EncodeDecode)
{
	static const doubles encoded {0, 0.0947343, 1.2848, 2.47487, 1.89718, 1.31948, 0, 0, 0, 0.353553, -0.482963, 0.612372, -0.12941, -0.353553, 0, 0};
	daub4double tr;

	doubles tmp = tr.forward(data, len);
	EXPECT_NEAR_VALUES(encoded, tmp, 4);

	tmp = tr.backward(tmp, len);
	EXPECT_NEAR_VALUES(data, tmp, 6);
}


TEST(OneDimTransformator, EncodeDecode)
{
	doubles bigdata(100);
	for (size_t i = 0; i < bigdata.size(); ++i)
		bigdata[i] = double(i);

	OneDimTransformator<double> tor;
	tor.set_transformation(new haardouble());

	doubles encoded1 = tor.apply_forward(bigdata);
	doubles decoded1 = tor.apply_backward(encoded1);

	EXPECT_NEAR_VALUES(bigdata, decoded1, 6);

	tor.set_transformation(new daub4double());
	doubles encoded2 = tor.apply_forward(bigdata);
	EXPECT_FAR_VALUES(encoded1, encoded2, 6);
	doubles decoded2 = tor.apply_backward(encoded2);

	EXPECT_NEAR_VALUES(bigdata, decoded2, 6);
}

/*
TEST(DividingTransformator, EncodeDecode)
{
	doubles bigdata(100);
	for (size_t i = 0; i < bigdata.size(); ++i)
		bigdata[i] = double(i);

	DividingTransformator<double> tor;
	tor.set_transformation(new haardouble());

	doubles encoded1 = tor.apply_forward(bigdata);
	doubles decoded1 = tor.apply_backward(encoded1);

	EXPECT_NEAR_VALUES(bigdata, decoded1, 6);

	tor.set_transformation(new daub4double());
	doubles encoded2 = tor.apply_forward(bigdata);
	EXPECT_FAR_VALUES(encoded1, encoded2, 6);
	doubles decoded2 = tor.apply_backward(encoded2);

	EXPECT_NEAR_VALUES(bigdata, decoded2, 6);
}


TEST(DividingTransformator, EncodeDecodeIntegers)
{
	uchars initial_data;
	for (size_t i = 0; i < 100; ++i)
		initial_data.push_back(i);
	doubles doubled_data = reset_vector_type<double>(initial_data);

	DividingTransformator<double> tor;

	tor.set_transformation(new haardouble());
	doubles encoded1 = tor.apply_forward(doubled_data);
	doubles decoded1 = tor.apply_backward(encoded1);
	EXPECT_NEAR_VALUES(doubled_data, decoded1, 6);
	EXPECT_EQ(initial_data, reset_vector_type<uchar>(decoded1));

	tor.set_transformation(new daub4double());
	doubles encoded2 = tor.apply_forward(doubled_data);
	doubles decoded2 = tor.apply_backward(encoded2);
	EXPECT_NEAR_VALUES(doubled_data, decoded2, 6);
	EXPECT_EQ(initial_data, reset_vector_type<uchar>(decoded2));

	EXPECT_FAR_VALUES(encoded1, encoded2, 6);
}
*/

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#endif
