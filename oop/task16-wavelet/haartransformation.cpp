#include "haartransformation.h"


void HaarTransformation::forward(Floats& vec) const
{
	const size_t n = vec.size();
	const size_t half_n = n / 2;
	Floats temp = Floats(n);

	for (size_t i = 0; i < half_n; ++i)
	{
		temp[i] = _half_sum(vec[i*2], vec[i*2 + 1]);
		temp[half_n + i] = _half_diff(vec[i*2], vec[i*2 + 1]);
	}

	temp.swap(vec);
}


void HaarTransformation::backward(Floats& vec) const
{
	const size_t n = vec.size();
	const size_t nh = n / 2;
	Floats temp = Floats(n);

	for (size_t i = 0; i < nh; ++i)
	{
		temp[i*2] = vec[i] + vec[nh + i];
		temp[i*2 + 1] = vec[i] - vec[nh + i];
	}

	temp.swap(vec);
}


float HaarTransformation::_half_sum(const float& a, const float& b) const
{
	return (a / 2 + b / 2);
}


float HaarTransformation::_half_diff(const float& a, const float& b) const
{
	return (a / 2 - b / 2);
}

