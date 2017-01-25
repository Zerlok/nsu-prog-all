#ifdef _DEBUG_

#include <gtest/gtest.h>
#include "../task16-wavelet/gtest_utils.h"

#include "cvtransformation.h"
#include "matrix.h"
#include "../task16-wavelet/haar.h"
#include "../task16-wavelet/daub4.h"
#include "../task16-wavelet/transformators.h"


static cv::Mat mat(16, 16, CV_8UC1);
using MatrixD = Matrix<double>;


void init_mat(cv::Mat& mat)
{
	for (size_t i = 0; i < size_t(mat.rows * mat.cols); ++i)
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


TEST(Matrix, mat2matrix)
{
	cv::Mat m(10, 10, CV_8UC1);
	init_mat(m);

	Matrix<int> mtrx = mat2matrix<int>(m);
	EXPECT_EQ(100, mtrx.size());

	for (size_t i = 0; i < mtrx.size(); ++i)
		EXPECT_EQ(m.data[i], mtrx[i]);

	EXPECT_EQ(m.row(7).data[0], mtrx.get_row(7)[0]);
	EXPECT_EQ(m.col(7).data[0], mtrx.get_col(7)[0]);
	EXPECT_EQ(m.data[98], mtrx.get_row(9)[8]);
	EXPECT_EQ(m.data[98], mtrx.get_col(8)[9]);

	EXPECT_EQ(m.row(3).data[7], mtrx(3, 7));

	cv::Mat m2 = matrix2mat(mtrx);
	EXPECT_EQ_MATS(m, m2);
}

TEST(Matrix, RowsCols)
{
	Matrix<int> mtrx(9, 9);
	for (size_t i = 0; i < mtrx.size(); ++i)
		mtrx[i] = i;

	Matrix<int>::Row row = mtrx.get_row(6);
	for (size_t i = 0; i < row.size(); ++i)
		row[i] = 0;

	Matrix<int>::Col col = mtrx.get_col(3);
	for (size_t i = 0; i < col.size(); ++i)
		col[i] = 0;

	for (size_t i = 0; i < mtrx.size(); ++i)
		EXPECT_EQ(i, mtrx[i]);

	mtrx.set_row(row);
	mtrx.set_col(col);

	for (size_t i = 0; i < mtrx.rows(); ++i)
		for (size_t j = 0; j < mtrx.cols(); ++j)
			if ((i != 6) && (j != 3))
				EXPECT_EQ((i * mtrx.cols() + j), mtrx(i, j));
			else
				EXPECT_EQ(0, mtrx(i, j));
}


TEST(Matrix, HaarTransformation)
{
	MatrixD data = mat2matrix<double>(mat);
	MatrixTransformator<double, HaarTransformation> tr;

	MatrixD tmp;
	tmp = tr.apply_forward(data);
	tmp = tr.apply_backward(tmp);

	EXPECT_NEAR_VALUES(data, tmp, 6) << data << tmp;
}


TEST(Matrix, DAUB4Transformation)
{
	MatrixD data = mat2matrix<double>(mat);
	MatrixTransformator<double, DAUB4Transformation> tr;
	MatrixD tmp;
	tmp = tr.apply_forward(data);
	tmp = tr.apply_backward(tmp);

	EXPECT_NEAR_VALUES(data, tmp, 6) << data << tmp;
}


int main(int argc, char *argv[])
{
	init_mat(mat);
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#endif
