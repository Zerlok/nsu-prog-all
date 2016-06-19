#include "daub4.h"


const double DAUB4Transform::c0 = 0.4829629131445341;
const double DAUB4Transform::c1 = 0.8365163037378079;
const double DAUB4Transform::c2 = 0.2241438680420134;
const double DAUB4Transform::c3 = -0.1294095225512604;


DAUB4Transform::Traits::DataSet DAUB4Transform::forward(
		const DAUB4Transform::Traits::DataSet& vec,
		const size_t& begin,
		const size_t& end) const
{
	const size_t len = std::min(end - begin, vec.size());
	Traits::DataSet tmp(vec);

	if (len < 4)
		return std::move(tmp);

//	for (size_t n = len; n >= 4; n >>= 1)
	const size_t last = len - 1;
	const size_t mid = len >> 1;

	size_t i, j;
	for (i = 0, j = 0;
		 j < last - 2;
		 i += 1, j += 2)
	{
		tmp[i] = c0*vec[j] + c1*vec[j+1] + c2*vec[j+2] + c3*vec[j+3];
		tmp[mid+i] = c3*vec[j] - c2*vec[j+1] + c1*vec[j+2] - c0*vec[j+3];
	}

	tmp[i] = c0*vec[last-1] + c1*vec[last] + c2*vec[0] + c3*vec[1];
	tmp[mid+i] = c3*vec[last-1] - c2*vec[last] + c1*vec[0] - c0*vec[1];

//	for (i = 0; i < n; ++i)
//		vec[i] = tmp[i];
	
	return std::move(tmp);
}


DAUB4Transform::Traits::DataSet DAUB4Transform::backward(
		const DAUB4Transform::Traits::DataSet& vec,
		const size_t& begin,
		const size_t& end) const
{
	const size_t len = std::min(end - begin, vec.size());
	Traits::DataSet tmp(vec);

	if (len < 4)
		return std::move(tmp);

	const size_t last = len - 1;
	const size_t mid = len >> 1;

	tmp[0] = c2*vec[mid-1] + c1*vec[last] + c0*vec[0] + c3*vec[mid];
	tmp[1] = c3*vec[mid-1] - c0*vec[last] + c1*vec[0] - c2*vec[mid];

	size_t i, j;
	for (i = 0, j = 2; i < mid-1; ++i)
	{
		tmp[j++] = c2*vec[i] + c1*vec[mid+i] + c0*vec[i+1] + c3*vec[mid+i+1];
		tmp[j++] = c3*vec[i] - c0*vec[mid+i] + c1*vec[i+1] - c2*vec[mid+i+1];
	}
	
	return std::move(tmp);
}
