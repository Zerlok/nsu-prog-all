#ifndef __TRANSFORMATION_H__
#define __TRANSFORMATION_H__


#include <vector>
#include <stddef.h>


template<class DataType, class DataSet>
class DataAdapter
{
	public:
		inline DataType& at(DataSet& data, const size_t& idx) const
		{
			return data[idx];
		}

		inline const DataType& at(const DataSet& data, const size_t& idx) const
		{
			return data[idx];
		}

		inline size_t size(const DataSet& data) const
		{
			return data.size();
		}

		DataSet clone(const DataSet& data) const
		{
			return std::move(DataSet(data));
		}
};


template<class DataType>
class TransformationTraits
{
	public:
		using Data = DataType;								// Working data type.
		using DataSet = std::vector<DataType>;				// Transformation data input type.
		using Adapter = DataAdapter<DataType, DataSet>;		// Size getter function.
};


template<class DataType>
class Transformation
{
	public:
		using Traits = TransformationTraits<DataType>;
		
		Transformation()
			: _adapter() {}
		virtual ~Transformation() {}
		virtual typename Traits::DataSet forward(const typename Traits::DataSet&, const size_t& end) const = 0;
		virtual typename Traits::DataSet backward(const typename Traits::DataSet&, const size_t& end) const = 0;
		
	protected:
		typename Traits::Adapter _adapter;
};


// __TRANSFORMATION_H__
#endif
