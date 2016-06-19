#ifndef __DAUB4_TRANSFORMATION_H__
#define __DAUB4_TRANSFORMATION_H__


#include "transformation.h"


class DAUB4Transform : public Transformation<double>
{
	public:
		virtual Traits::DataSet forward(const Traits::DataSet& vec, const size_t& begin, const size_t& end) const override;
		virtual Traits::DataSet backward(const Traits::DataSet& vec, const size_t& begin, const size_t& end) const override;

	private:
		static const double c0;
		static const double c1;
		static const double c2;
		static const double c3;
};


// __DAUB4_TRANSFORMATION_H__
#endif
