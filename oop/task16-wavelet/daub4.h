#ifndef __DAUB4_TRANSFORMATION_H__
#define __DAUB4_TRANSFORMATION_H__


#include "transformation.h"


template<class DataType,
		 class DataTrans = typename TransformationTraits<DataType>::DataTransform>
class DAUB4Transformation : public Transformation<DataType, DataTrans>
{
	public:
		using super = Transformation<DataType, DataTrans>;

		virtual DataTrans forward(
				const DataTrans& data,
				const size_t& end) const override
		{
			const size_t len = std::min(end, data.size());
			DataTrans tmp(data);

			if (len < 4)
				return std::move(tmp);

			const size_t last = len - 1;
			const size_t mid = len >> 1;

			size_t i, j;
			for (i = 0, j = 0;
				 j < last - 2;
				 i += 1, j += 2)
			{
				tmp[i] = c0 * data[j] + c1 * data[j+1] + c2 * data[j+2] + c3 * data[j+3];
				tmp[mid+i] = c3 * data[j] - c2 * data[j+1] + c1 * data[j+2] - c0 * data[j+3];
			}

			tmp[i] = c0 * data[last-1] + c1 * data[last] + c2 * data[0] + c3 * data[1];
			tmp[mid+i] = c3 * data[last-1] - c2 * data[last] + c1 * data[0] - c0 * data[1];

			return std::move(tmp);
		}

		virtual DataTrans backward(
				const DataTrans& data,
				const size_t& end) const override
		{
			const size_t len = std::min(end, data.size());
			DataTrans tmp(data);

			if (len < 4)
				return std::move(tmp);

			const size_t last = len - 1;
			const size_t mid = len >> 1;

			tmp[0] = c2 * data[mid-1] + c1 * data[last] + c0 * data[0] + c3 * data[mid];
			tmp[1] = c3 * data[mid-1] - c0 * data[last] + c1 * data[0] - c2 * data[mid];

			size_t i, j;
			for (i = 0, j = 2; i < mid-1; ++i)
			{
				tmp[j++] = c2 * data[i] + c1 * data[mid+i] + c0 * data[i+1] + c3 * data[mid+i+1];
				tmp[j++] = c3 * data[i] - c0 * data[mid+i] + c1 * data[i+1] - c2 * data[mid+i+1];
			}

			return std::move(tmp);
		}

	private:
		static const double c0;
		static const double c1;
		static const double c2;
		static const double c3;
};


template<class DataType, class DataTrans>
const double DAUB4Transformation<DataType, DataTrans>::c0 = 0.4829629131445341;

template<class DataType, class DataTrans>
const double DAUB4Transformation<DataType, DataTrans>::c1 = 0.8365163037378079;

template<class DataType, class DataTrans>
const double DAUB4Transformation<DataType, DataTrans>::c2 = 0.2241438680420134;

template<class DataType, class DataTrans>
const double DAUB4Transformation<DataType, DataTrans>::c3 = -0.1294095225512604;


// __DAUB4_TRANSFORMATION_H__
#endif
