#ifndef __HAAR_TRANSFORMATION_H__
#define __HAAR_TRANSFORMATION_H__


#include <vector>
#include "transformation.h"


template <class DataType,
		  class DataTrans = typename TransformationTraits<DataType>::DataTransform >
class HaarTransformation : public Transformation<DataType, DataTrans>
{
	public:
		using super = Transformation<DataType, DataTrans>;
		
		DataTrans forward(const DataTrans& data,
						  const size_t& end) const override
		{
			const size_t len = std::min(end, data.size());
			const size_t mid = len / 2;
			DataTrans tmp(data);

			for (size_t i = 0; i < mid; ++i)
			{
				tmp[i] = _half_sum(data[i*2], data[i*2 + 1]);
				tmp[mid+i] = _half_diff(data[i*2], data[i*2 + 1]);
			}

			return std::move(tmp);
		}

		DataTrans backward(const DataTrans& data,
						   const size_t& end) const override
		{
			const size_t len = std::min(end, data.size());
			const size_t mid = len / 2;
			DataTrans tmp(data);

			for (size_t i = 0; i < mid; ++i)
			{
				tmp[i*2] = data[i] + data[mid + i];
				tmp[i*2 + 1] = data[i] - data[mid + i];
			}

			return std::move(tmp);
		}

	private:
		inline DataType _half_sum(
				const DataType& a,
				const DataType& b) const
		{
			return ((a / 2) + (b / 2));
		}

		inline DataType _half_diff(
				const DataType& a,
				const DataType& b) const
		{
			return ((a / 2) - (b / 2));
		}
};


// __HAAR_TRANSFORMATION_H__
#endif
