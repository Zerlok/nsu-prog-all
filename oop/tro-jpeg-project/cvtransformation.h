#ifndef __CV_TRANSFORMATION_TRAITS_H__
#define __CV_TRANSFORMATION_TRAITS_H__


#include <opencv/cv.h>
#include "matrix.h"
#include "../task16-wavelet/transformation.h"
#include "../task16-wavelet/transformators.h"


template<class T>
class TransformationTraits< Matrix<T> >
{
	public:
		using Data = T;
		using DataTransform = typename Matrix<T>::Range;
};


template<class T>
class TransformatorTraits< Matrix<T> >
{
	public:
		using TransformationType = Transformation< Matrix<T> >;
		using Data = typename TransformationType::Traits::Data;
		using DataInput = Matrix<T>;
		using DataTransform = typename TransformationType::Traits::DataTransform;
};


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


template<class MatrixT>
class MatrixTransformator : public Transformator<MatrixT>
{
	public:
		using super = Transformator<MatrixT>;

		MatrixT apply_forward(const MatrixT& mat) const
		{
			MatrixT tmp(mat.rows(), mat.cols());
			typename MatrixT::Row row;
			typename MatrixT::Col col;

			for (size_t r = 0; r < tmp.rows(); ++r)
			{
				row = mat.get_row(r);
				super::_tr->forward(row, row.size());
			}

			for (size_t c = 0; c < tmp.cols(); ++c)
			{
				col = tmp.get_col(c);
				super::_tr->forward(col, col.size());
			}

			return std::move(tmp);
		}

		MatrixT apply_backward(const MatrixT& mat) const
		{
			MatrixT tmp(mat.rows(), mat.cols());
			typename MatrixT::Row row;
			typename MatrixT::Col col;

			for (size_t c = 0; c < tmp.cols(); ++c)
			{
				col = mat.get_col(c);
				super::_tr->backward(col, col.size());
			}

			for (size_t r = 0; r < tmp.rows(); ++r)
			{
				row = mat.get_row(r);
				super::_tr->backward(tmp.get_row(r), row.si);
			}

			return std::move(tmp);
		}
};


// __CV_TRANSFORMATION_TRAITS_H__
#endif

