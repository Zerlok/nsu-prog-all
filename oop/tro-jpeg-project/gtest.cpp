#ifdef _DEBUG_

#include <gtest/gtest.h>

#include "cvtransformation.h"
#include "../task16-wavelet/haar.h"
#include "../task16-wavelet/daub4.h"
#include "../task16-wavelet/transformators.h"


using MatAdapter = typename TransformationTraits<cv::Mat>::Adapter;
static const MatAdapter adapter;
static cv::Mat mat(8, 8, CV_8UC1);


void init_mat(cv::Mat& mat)
{
	for (size_t i = 0; i < (mat.rows * mat.cols); ++i)
		mat.data[i] = i;
}


::testing::AssertionResult eq_mats(const cv::Mat& mat1, const cv::Mat& mat2)
{
	const size_t len1 = (mat1.rows * mat1.cols);
	const size_t len2 = (mat2.rows * mat2.cols);

	if (len1 != len2)
		return ::testing::AssertionFailure() << "mats have different amount of data: " << len1 << " and " << len2;

	for (size_t i = 0; i < len1; ++i)
		if (mat1.data[i] != mat2.data[i])
			return ::testing::AssertionFailure()
					<< "mats are different at "<< i << " pos ("
					<< (i / mat1.cols) << ", " << (i % mat1.cols) << ")";

	return ::testing::AssertionSuccess() << "mats contains the same values.";
}
#define EXPECT_EQ_MATS(mat1, mat2) EXPECT_TRUE(eq_mats(mat1, mat2))


TEST(cvMat, ColsRows)
{
	MatTransformator mator;
	cv::Mat m(10, 10, CV_8UC1);
	init_mat(m);
	const size_t c = 3;
	const size_t r = 7;
	cv::Mat col = mator.get_column(m, c);
	cv::Mat row = mator.get_row(m, r);

	for (size_t i = 0; i < size_t(m.rows); ++i)
		EXPECT_EQ(m.data[(i*m.cols) + c], col.data[i]);

	for (size_t i = 0; i < size_t(m.rows); ++i)
		EXPECT_EQ(m.data[(r*m.cols) + i], row.data[i]);
}


TEST(cvMat, HaarTransformation)
{
	MatTransformator tr;
	tr.set_transformation(new HaarTransformation<cv::Mat>());
	cv::Mat tmp;
	tmp = tr.apply_forward(mat);
	tmp = tr.apply_backward(tmp);
	EXPECT_EQ_MATS(mat, tmp)
			<< mat << std::endl << tmp;
}


TEST(cvMat, DAUB4Transformation)
{
	MatTransformator tr;
	cv::Mat tmp;
	tr.set_transformation(new DAUB4Transformation<cv::Mat>());
	tmp = tr.apply_forward(mat);
	tmp = tr.apply_backward(tmp);
	EXPECT_EQ_MATS(mat, tmp)
			<< mat << std::endl << tmp;
}


int main(int argc, char *argv[])
{
	init_mat(mat);
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#endif
