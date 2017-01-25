#ifndef __TRANSFORMATORS_H__
#define __TRANSFORMATORS_H__


#include <vector>
#include "transformation.h"


template<class DataType,
		 class DataIn = typename TransformationTraits<DataType>::DataTransform,
		 class TransType = Transformation<DataType, DataIn> >
class TransformatorTraits
{
	public:
		using DataInput = DataIn;				// What transformator takes on input (input data type).
		using TransformationType = TransType;	// Transformation type.
};


template<class DataType,
		 class DataIn = typename TransformatorTraits<DataType>::DataInput,
		 class TransType = typename TransformatorTraits<DataType, DataIn>::TransformationType>
class Transformator
{
	public:
		using Traits = TransformatorTraits<DataType, DataIn, TransType>;
		
		Transformator()
			: _tr(nullptr) {}
		virtual ~Transformator() { delete _tr; }

		virtual DataIn apply_forward(const DataIn&) const = 0;
		virtual DataIn apply_backward(const DataIn&) const = 0;

		void set_transformation(const TransType* tr)
		{
			delete _tr;
			_tr = tr;
		}

	protected:
		const TransType* _tr;
};


template<class DataType,
		 class DataIn = typename TransformatorTraits<DataType>::DataInput,
		 class TransType = typename TransformatorTraits<DataType, DataIn>::TransformationType>
class OneDimTransformator : public Transformator<DataType, DataIn, TransType>
{
	public:
		using super = Transformator<DataType, DataIn, TransType>;
				
		DataIn apply_forward(const DataIn& data) const override
		{
			return super::_tr->forward(data, data.size());
		}
		
		DataIn apply_backward(const DataIn& data) const override
		{
			return super::_tr->backward(data, data.size());
		}
};


template<class DataType,
		 class DataIn = typename TransformatorTraits<DataType>::DataInput,
		 class TransType = typename TransformatorTraits<DataType, DataIn>::TransformationType>
class DividingTransformator : public Transformator<DataType, DataIn, TransType>
{
	public:
		using super = Transformator<DataType, DataIn, TransType>;

		DataIn apply_forward(const DataIn& data) const override
		{
			DataIn tmp(data);
			DataIn line;
			for (size_t n = data.size(); n >= 4; n >>= 1)
			{
				line = super::_tr->forward(tmp, n);
				for (size_t i = 0; i < n; ++i)
					tmp[i] = line[i];
			}
			
			return std::move(tmp);
		}
		
		DataIn apply_backward(const DataIn& data) const override
		{
			DataIn tmp(data);
			DataIn line;
			for (size_t n = 4; n <= data.size(); n <<= 1)
			{
				line = super::_tr->backward(tmp, n);
				for (size_t i = 0; i < n; ++i)
					tmp[i] = line[i];
			}
			
			return std::move(tmp);
		}
};


// __TRANSFORMATORS_H__
#endif
