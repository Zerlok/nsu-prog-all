#ifdef _DEBUG_

#include <gtest/gtest.h>

#include "haar.h"
#include "daub4.h"
#include "transformators.h"
#include "utils.h"


using doubles = std::vector<double>;
using haardouble = HaarTransformation<double>;
using daub4double = DAUB4Transformation<double>;


static const doubles data {0, 0, 0, 0, 1, 1, 1, 2, 2, 1, 1, 1, 0, 0, 0, 0};
static const size_t len = data.size();


TEST(HaarTransformation, EncodeDecode)
{
	static const doubles encoded { 0, 0, 1, 1.5, 1.5, 1, 0, 0, 0, 0, -0.5, 0.5, 0, 0, 0, 0};
	haardouble tr;

	doubles tmp = tr.forward(data, len-2);
	EXPECT_EQ(encoded, tmp);

	tmp = tr.backward(tmp, len-2);
	EXPECT_EQ(data, tmp);
}


TEST(DAUB4, EncodeDecode)
{
	static const doubles encoded {0, 0.0947343, 1.2848, 2.47487, 1.89718, 1.31948, 0, 0, 0.353553, -0.482963, 0.612372, -0.12941, -0.353553, 0, 0, 0};
	daub4double tr;

	doubles tmp = tr.forward(data, len-2);
	EXPECT_NEAR_VALUES(encoded, tmp, 4);

	tmp = tr.backward(tmp, len-2);
	EXPECT_NEAR_VALUES(data, tmp, 6);
}


TEST(OneDimTransformator, EncodeDecode)
{
	OneDimTransformator<double> tor;
	tor.set_transformation(new haardouble());

	doubles encoded1 = tor.apply_forward(data);
	doubles decoded1 = tor.apply_backward(encoded1);

	EXPECT_NEAR_VALUES(data, decoded1, 6);

	tor.set_transformation(new daub4double());
	doubles encoded2 = tor.apply_forward(data);
	EXPECT_FAR_VALUES(encoded1, encoded2, 6);
	doubles decoded2 = tor.apply_backward(encoded2);

	EXPECT_NEAR_VALUES(data, decoded2, 6);
}


TEST(DividingTransformator, EncodeDecode)
{
	DividingTransformator<double> tor;
	tor.set_transformation(new haardouble());

	doubles encoded1 = tor.apply_forward(data);
	doubles decoded1 = tor.apply_backward(encoded1);

	EXPECT_NEAR_VALUES(data, decoded1, 6);

	tor.set_transformation(new daub4double());
	doubles encoded2 = tor.apply_forward(data);
	EXPECT_FAR_VALUES(encoded1, encoded2, 6);
	doubles decoded2 = tor.apply_backward(encoded2);

	EXPECT_NEAR_VALUES(data, decoded2, 6);
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#endif
