#ifndef __TRANSFORMATION_H__
#define __TRANSFORMATION_H__


#include <vector>
#include <stddef.h>


template<class DataSet>
class DataSizeGetter
{
	public:
		size_t operator()(const DataSet& data) const { return data.size(); }
};


template<class DataType>
class TransformationTraits
{
	public:
		using Data = DataType;							// Working data type.
		using DataSet = std::vector<DataType>;			// Transformation data input type.
		using SizeGetter = DataSizeGetter<DataSet>;		// Size getter function.
};


template<class DataType>
class Transformation
{
	public:
		using Traits = TransformationTraits<DataType>;
		
		virtual ~Transformation() {}
		virtual typename Traits::DataSet forward(const typename Traits::DataSet&, const size_t& begin, const size_t& end) const = 0;
		virtual typename Traits::DataSet backward(const typename Traits::DataSet&, const size_t& begin, const size_t& end) const = 0;
		
	protected:
		typename Traits::SizeGetter _getsize;
};


// __TRANSFORMATION_H__
#endif
