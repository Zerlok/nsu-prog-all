#ifndef __TRANSFORMATION_H__
#define __TRANSFORMATION_H__


#include <vector>
#include <stddef.h>


template<class DataType, class DataTrans = std::vector<DataType> >
class TransformationTraits
{
	public:
		using Data = DataType;				// Data base type.
		using DataTransform = DataTrans;	// Transformation data input type.
};


template<class DataType,
		 class DataTrans = typename TransformationTraits<DataType>::DataTransform >
class Transformation
{
	public:
		using Traits = TransformationTraits<DataType, DataTrans>;
		
		virtual ~Transformation() {}
		virtual DataTrans forward(const DataTrans&, const size_t& end) const = 0;
		virtual DataTrans backward(const DataTrans&, const size_t& end) const = 0;
};


// __TRANSFORMATION_H__
#endif
