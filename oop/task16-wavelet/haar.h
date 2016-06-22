#ifndef __HAAR_TRANSFORMATION_H__
#define __HAAR_TRANSFORMATION_H__


#include <vector>
#include "transformation.h"


template <class DataType>
class HaarTransformation : public Transformation<DataType>
{
	public:
		using super = Transformation<DataType>;
		
		typename super::Traits::DataSet forward(
				const typename super::Traits::DataSet& data,
				const size_t& end) const override
		{
			const size_t len = std::min(end, super::_adapter.size(data));
			const size_t mid = len / 2;
			typename super::Traits::DataSet tmp = super::_adapter.clone(data);

			for (size_t i = 0; i < mid; ++i)
			{
				super::_adapter.at(tmp, i) = _half_sum(super::_adapter.at(data, i*2), super::_adapter.at(data, i*2 + 1));
				super::_adapter.at(tmp, mid + i) = _half_diff(super::_adapter.at(data, i*2), super::_adapter.at(data, i*2 + 1));
			}

			return std::move(tmp);
		}

		typename super::Traits::DataSet backward(
				const typename super::Traits::DataSet& data,
				const size_t& end) const override
		{
			const size_t len = std::min(end, super::_adapter.size(data));
			const size_t mid = len / 2;
			typename super::Traits::DataSet tmp = super::_adapter.clone(data);

			for (size_t i = 0; i < mid; ++i)
			{
				super::_adapter.at(tmp, i*2) = super::_adapter.at(data, i) + super::_adapter.at(data, mid + i);
				super::_adapter.at(tmp, i*2 + 1) = super::_adapter.at(data, i) - super::_adapter.at(data, mid + i);
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
