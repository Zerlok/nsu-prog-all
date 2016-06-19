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
		using SizeGetter = typename DataTransformation::Traits::SizeGetter;
};


template<class DataType, class TraitsType = TransformatorTraits<DataType> >
class Transformator
{
	public:
		using Traits = TraitsType;
		
		virtual ~Transformator() { delete _tr; }

		virtual typename Traits::DataSet apply_forward(const typename Traits::DataSet&) = 0;
		virtual typename Traits::DataSet apply_backward(const typename Traits::DataSet&) = 0;

		void set_transformation(const typename Traits::DataTransformation* tr)
		{
			delete _tr;
			_tr = tr;
		}

	protected:
		const typename Traits::DataTransformation* _tr;
		typename Traits::SizeGetter _getsize;
};


template<class DataType>
class OneDimTransformator : public Transformator<DataType>
{
	public:
		using super = Transformator<DataType>;
				
		typename super::Traits::DataSet apply_forward(
				const typename super::Traits::DataSet& data) override
		{
			return super::_tr->forward(data, 0, super::_getsize(data));
		}
		
		typename super::Traits::DataSet apply_backward(
				const typename super::Traits::DataSet& data) override
		{
			return super::_tr->backward(data, 0, super::_getsize(data));
		}
};


template<class DataType>
class DividingTransformator : public Transformator<DataType>
{
	public:
		using super = Transformator<DataType>;
		
		typename super::DataSet apply_forward(
				const typename super::DataSet& data) override
		{
			typename super::DataSet tmp(data);
			for (size_t n = super::_getsize(data); n >= 4; n >>= 1)
				tmp = super::_tr->forward(tmp, 0, n);
			
			return std::move(tmp);
		}
		
		typename super::DataSet apply_backward(
				const typename super::DataSet& data) override
		{
			typename super::DataSet tmp(data);
			for (size_t n = 2; n < super::_getsize(tmp); n <<= 1)
				tmp = super::_tr->backward(tmp, 0, n);
			
			return std::move(tmp);
		}
};


// __TRANSFORMATORS_H__
#endif