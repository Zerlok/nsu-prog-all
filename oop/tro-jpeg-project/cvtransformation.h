#ifndef __CV_TRANSFORMATION_TRAITS_H__
#define __CV_TRANSFORMATION_TRAITS_H__


#include <opencv/cv.h>
#include "matrix.h"
#include "../task16-wavelet/transformation.h"
#include "../task16-wavelet/transformators.h"


template<class T>
Matrix<T> mat2matrix(const cv::Mat& from)
{
	const size_t len = (from.rows * from.cols);
	Matrix<T> to(from.rows, from.cols);
	for (size_t i = 0; i < len; ++i)
		to[i] = T(from.data[i]);

	return std::move(to);
}


template<class T>
static cv::Mat matrix2mat(const Matrix<T>& from)
{
	const size_t len = (from.rows() * from.cols());
	cv::Mat to(from.rows(), from.cols(), CV_8UC1);
	for (size_t i = 0; i < len; ++i)
		to.data[i] = uchar(std::round(from[i]));

	return std::move(to);
}


template<class T, template <class, class> class Transformation>
class MatrixTransformator
{
	public:
		using MatrixT = Matrix<T>;
		using MatrixRow = typename MatrixT::Row;
		using MatrixCol = typename MatrixT::Col;
		using RowTransformator = OneDimTransformator<T, MatrixRow>;
		using ColTransformator = OneDimTransformator<T, MatrixCol>;

		MatrixTransformator()
		{
			_rowtor.set_transformation(new Transformation<T, MatrixRow>());
			_coltor.set_transformation(new Transformation<T, MatrixCol>());
		}

		MatrixT apply_forward(const MatrixT& mtrx) const
		{
			MatrixT tmp(mtrx.rows(), mtrx.cols());
			MatrixRow mtrx_row;
			MatrixCol mtrx_col;

			for (size_t r = 0; r < tmp.rows(); ++r)
			{
				mtrx_row = mtrx.get_row(r);
				mtrx_row = _rowtor.apply_forward(mtrx_row);
				tmp.set_row(mtrx_row);
			}

			for (size_t c = 0; c < tmp.cols(); ++c)
			{
				mtrx_col = tmp.get_col(c);
				mtrx_col = _coltor.apply_forward(mtrx_col);
				tmp.set_col(mtrx_col);
			}

			return std::move(tmp);
		}

		MatrixT apply_backward(const MatrixT& mtrx) const
		{
			MatrixT tmp(mtrx.rows(), mtrx.cols());
			MatrixRow mtrx_row;
			MatrixCol mtrx_col;

			for (size_t c = 0; c < tmp.cols(); ++c)
			{
				mtrx_col = mtrx.get_col(c);
				mtrx_col = _coltor.apply_backward(mtrx_col);
				tmp.set_col(mtrx_col);
			}

			for (size_t r = 0; r < tmp.rows(); ++r)
			{
				mtrx_row = tmp.get_row(r);
				mtrx_row = _rowtor.apply_backward(mtrx_row);
				tmp.set_row(mtrx_row);
			}

			return std::move(tmp);
		}

	private:
		RowTransformator _rowtor;
		ColTransformator _coltor;
};


// __CV_TRANSFORMATION_TRAITS_H__
#endif

