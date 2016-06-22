#ifndef __DAUB4_TRANSFORMATION_H__
#define __DAUB4_TRANSFORMATION_H__


#include "transformation.h"


template<class DataType>
class DAUB4Transformation : public Transformation<DataType>
{
	public:
		using super = Transformation<DataType>;

		virtual typename super::Traits::DataTransform forward(
				const typename super::Traits::DataTransform& vec,
				const size_t& end) const override
		{
			const size_t len = std::min(end, vec.size());
			typename super::Traits::DataTransform tmp(len);

			if (len < 4)
				return std::move(tmp);

			const size_t last = len - 1;
			const size_t mid = len >> 1;

			size_t i, j;
			for (i = 0, j = 0;
				 j < last - 2;
				 i += 1, j += 2)
			{
				tmp[i] = c0 * vec[j] + c1 * vec[j+1] + c2 * vec[j+2] + c3 * vec[j+3];
				tmp[mid+i] = c3 * vec[j] - c2 * vec[j+1] + c1 * vec[j+2] - c0 * vec[j+3];
			}

			tmp[i] = c0 * vec[last-1] + c1 * vec[last] + c2 * vec[0] + c3 * vec[1];
			tmp[mid+i] = c3 * vec[last-1] - c2 * vec[last] + c1 * vec[0] - c0 * vec[1];

			return std::move(tmp);
		}

		virtual typename super::Traits::DataTransform backward(
				const typename super::Traits::DataTransform& vec,
				const size_t& end) const override
		{
			const size_t len = std::min(end, vec.size());
			typename super::Traits::DataTransform tmp(len);

			if (len < 4)
				return std::move(tmp);

			const size_t last = len - 1;
			const size_t mid = len >> 1;

			tmp[0] = c2 * vec[mid-1] + c1 * vec[last] + c0 * vec[0] + c3 * vec[mid];
			tmp[1] = c3 * vec[mid-1] - c0 * vec[last] + c1 * vec[0] - c2 * vec[mid];

			size_t i, j;
			for (i = 0, j = 2; i < mid-1; ++i)
			{
				tmp[j++] = c2 * vec[i] + c1 * vec[mid+i] + c0 * vec[i+1] + c3 * vec[mid+i+1];
				tmp[j++] = c3 * vec[i] - c0 * vec[mid+i] + c1 * vec[i+1] - c2 * vec[mid+i+1];
			}

			return std::move(tmp);
		}

	private:
		static const double c0;
		static const double c1;
		static const double c2;
		static const double c3;
};


template<class DataType>
const double DAUB4Transformation<DataType>::c0 = 0.4829629131445341;
template<class DataType>
const double DAUB4Transformation<DataType>::c1 = 0.8365163037378079;
template<class DataType>
const double DAUB4Transformation<DataType>::c2 = 0.2241438680420134;
template<class DataType>
const double DAUB4Transformation<DataType>::c3 = -0.1294095225512604;


// __DAUB4_TRANSFORMATION_H__
#endif
