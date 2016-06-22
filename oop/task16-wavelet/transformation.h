#ifndef __TRANSFORMATION_H__
#define __TRANSFORMATION_H__


#include <vector>
#include <stddef.h>


template<class DataType>
class TransformationTraits
{
	public:
		using Data = DataType;							// Data base type.
		using DataTransform = std::vector<DataType>;	// Transformation data input type.
};


template<class DataType>
class Transformation
{
	public:
		using Traits = TransformationTraits<DataType>;
		
		virtual ~Transformation() {}
		virtual typename Traits::DataTransform forward(const typename Traits::DataTransform&, const size_t& end) const = 0;
		virtual typename Traits::DataTransform backward(const typename Traits::DataTransform&, const size_t& end) const = 0;
};


// __TRANSFORMATION_H__
#endif
