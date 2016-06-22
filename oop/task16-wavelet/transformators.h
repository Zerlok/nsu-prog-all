#ifndef __TRANSFORMATORS_H__
#define __TRANSFORMATORS_H__


#include <vector>
#include "transformation.h"


template<class DataType>
class TransformatorTraits
{
	public:
		using TransformationType = Transformation<DataType>;
		using Data = typename TransformationType::Traits::Data;
		using DataTransform = typename TransformationType::Traits::DataTransform;
		using DataInput = DataTransform;
};


template<class DataType>
class Transformator
{
	public:
		using Traits = TransformatorTraits<DataType>;
		
		Transformator()
			: _tr(nullptr) {}
		virtual ~Transformator() { delete _tr; }

		virtual typename Traits::DataInput apply_forward(const typename Traits::DataInput&) const = 0;
		virtual typename Traits::DataInput apply_backward(const typename Traits::DataInput&) const = 0;

		void set_transformation(const typename Traits::TransformationType* tr)
		{
			delete _tr;
			_tr = tr;
		}

	protected:
		const typename Traits::TransformationType* _tr;
};


template<class DataType>
class OneDimTransformator : public Transformator<DataType>
{
	public:
		using super = Transformator<DataType>;
				
		typename super::Traits::DataInput apply_forward(
				const typename super::Traits::DataInput& data) const override
		{
			return super::_tr->forward(data, data.size());
		}
		
		typename super::Traits::DataInput apply_backward(
				const typename super::Traits::DataInput& data) const override
		{
			return super::_tr->backward(data, data.size());
		}
};


template<class DataType>
class DividingTransformator : public Transformator<DataType>
{
	public:
		using super = Transformator<DataType>;
				
		typename super::Traits::DataInput apply_forward(
				const typename super::Traits::DataInput& data) const override
		{
			typename super::Traits::DataInput tmp(data);
			typename super::Traits::DataTransform line;
			for (size_t n = data.size(); n >= 4; n >>= 1)
			{
				line = super::_tr->forward(tmp, n);
				for (size_t i = 0; i < n; ++i)
					tmp[i] = line[i];
			}
			
			return std::move(tmp);
		}
		
		typename super::Traits::DataInput apply_backward(
				const typename super::Traits::DataInput& data) const override
		{
			typename super::Traits::DataInput tmp(data);
			typename super::Traits::DataTransform line;
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
