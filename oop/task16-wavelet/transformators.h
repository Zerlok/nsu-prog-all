#ifndef __TRANSFORMATORS_H__
#define __TRANSFORMATORS_H__


#include <vector>
#include "transformation.h"


template<class DataType>
class TransformatorTraits
{
	public:
		using DataTransformation = Transformation<DataType>;
		using Data = typename DataTransformation::Traits::Data;
		using DataSet = typename DataTransformation::Traits::DataSet;
		using Adapter = typename DataTransformation::Traits::Adapter;
};


template<class DataType, class TraitsType = TransformatorTraits<DataType> >
class Transformator
{
	public:
		using Traits = TraitsType;
		
		Transformator()
			: _tr(nullptr), _adapter() {}
		virtual ~Transformator() { delete _tr; }

		virtual typename Traits::DataSet apply_forward(const typename Traits::DataSet&) const = 0;
		virtual typename Traits::DataSet apply_backward(const typename Traits::DataSet&) const = 0;

		void set_transformation(const typename Traits::DataTransformation* tr)
		{
			delete _tr;
			_tr = tr;
		}

	protected:
		const typename Traits::DataTransformation* _tr;
		const typename Traits::Adapter _adapter;
};


template<class DataType>
class OneDimTransformator : public Transformator<DataType>
{
	public:
		using super = Transformator<DataType>;
				
		typename super::Traits::DataSet apply_forward(
				const typename super::Traits::DataSet& data) const override
		{
			return super::_tr->forward(data, super::_adapter.size(data));
		}
		
		typename super::Traits::DataSet apply_backward(
				const typename super::Traits::DataSet& data) const override
		{
			return super::_tr->backward(data, super::_adapter.size(data));
		}
};


template<class DataType>
class DividingTransformator : public Transformator<DataType>
{
	public:
		using super = Transformator<DataType>;
				
		typename super::Traits::DataSet apply_forward(
				const typename super::Traits::DataSet& data) const override
		{
			typename super::Traits::DataSet tmp(data);
			for (size_t n = super::_adapter.size(data); n >= 4; n >>= 1)
				tmp = super::_tr->forward(tmp, n);
			
			return std::move(tmp);
		}
		
		typename super::Traits::DataSet apply_backward(
				const typename super::Traits::DataSet& data) const override
		{
			typename super::Traits::DataSet tmp(data);
			for (size_t n = 4; n <= super::_adapter.size(tmp); n <<= 1)
				tmp = super::_tr->backward(tmp, n);
			
			return std::move(tmp);
		}
};


// __TRANSFORMATORS_H__
#endif
