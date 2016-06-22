#ifndef __HAAR_TRANSFORMATION_H__
#define __HAAR_TRANSFORMATION_H__


#include <vector>
#include "transformation.h"


template <class DataType>
class HaarTransformation : public Transformation<DataType>
{
	public:
		using super = Transformation<DataType>;
		
		typename super::Traits::DataTransform forward(
				const typename super::Traits::DataTransform& data,
				const size_t& end) const override
		{
			const size_t len = std::min(end, data.size());
			const size_t mid = len / 2;
			typename super::Traits::DataTransform tmp(len);

			for (size_t i = 0; i < mid; ++i)
			{
				tmp[i] = _half_sum(data[i*2], data[i*2 + 1]);
				tmp[mid+i] = _half_diff(data[i*2], data[i*2 + 1]);
			}

			return std::move(tmp);
		}

		typename super::Traits::DataTransform backward(
				const typename super::Traits::DataTransform& data,
				const size_t& end) const override
		{
			const size_t len = std::min(end, data.size());
			const size_t mid = len / 2;
			typename super::Traits::DataTransform tmp(len);

			for (size_t i = 0; i < mid; ++i)
			{
				tmp[i*2] = data[i] + data[mid + i];
				tmp[i*2 + 1] = data[i] - data[mid + i];
			}

			return std::move(tmp);
		}

	private:
		inline typename super::Traits::Data _half_sum(
				const typename super::Traits::Data& a,
				const typename super::Traits::Data& b) const
		{
			return ((a / 2) + (b / 2));
		}

		inline typename super::Traits::Data _half_diff(
				const typename super::Traits::Data& a,
				const typename super::Traits::Data& b) const
		{
			return ((a / 2) - (b / 2));
		}
};


// __HAAR_TRANSFORMATION_H__
#endif
