#include <iostream>
#include <vector>
#include <cmath>
#include "haartransformation.h"
#include "wtr.h"


template<class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec)
{
	const size_t len = vec.size();
	std::cout << "len: " << len << " {";
	for (const T& v : vec)
		std::cout << v << ", ";

	if (len > 0)
		std::cout << "\b\b";

	std::cout << '}' << std::endl;
	return out;
}


std::ostream& operator<<(std::ostream& out, const typename std::vector<int>::iterator& it)
{
	return out << (*it) << ": " << &(*it);
}


static const int NMAX = 512;
static const float RBEG = 0.25;
static const float REND = 0.75;
static const float bottom = 0.0;
static const float top = 1.0;


int main(void)
{
	int k;
	bool invalid_k;
	float frac, thresh, tmp;
	size_t nbeg, nend, num;
	size_t zeroes;

	OneDimTransformator transformator;

	for (;;)
	{
		/* DATA READ BLOCK */
		std::cout << "Enter k [-2 - Haar, -4 - DAUB4, 4, 12, 20]" << std::endl
				  << "compressing ratio (0.0 <= frac <= 1.0)" << std::endl
				  << "len of data (if 0 then 512):" << std::endl;
		std::cin >> k >> frac >> num;
		invalid_k = false;
		if (num == 0)
			num = NMAX;
		nbeg = RBEG * num;
		nend = REND * num;

		Floats modifying_data(num);
		Floats initial_data(num);

		frac = std::min(top, std::max(frac, bottom));
		/* SET TRANSFORMATION FROM K */
		switch (k)
		{
			case -2:
				transformator.set_transformation(new HaarTransformation());
				break;

			case -4:
				transformator.set_transformation(new DAUB4Transform());
				break;

			case 4:
				transformator.set_transformation(new PartlyTransform(PartlyTransform::Filt::Mode::first));
				break;

			case 12:
				transformator.set_transformation(new PartlyTransform(PartlyTransform::Filt::Mode::second));
				break;

			case 20:
				transformator.set_transformation(new PartlyTransform(PartlyTransform::Filt::Mode::third));
				break;

			default:
				invalid_k = true;
				break;
		}

		if (invalid_k)
			continue;

		/* SET INITIAL DATA */
		for (size_t i = 0; i < num; ++i)
			if ((i > nbeg) && (i < nend))
				initial_data[i] = modifying_data[i] = ((float(nend-i) * float(i-nbeg) * 4) / ((nend - nbeg)*(nend-nbeg)));
		std::cout << "INIT:" << std::endl
				  << initial_data << std::endl;

		/* DO TRANSFORMATION */
		transformator.apply_forward(modifying_data);
		std::cout << "ENCODED:" << std::endl
				  << modifying_data << std::endl;

		/* DO COMPRESSING */
		zeroes = 0;
		for (size_t i = 0; i < num; ++i)
		{
			if (std::abs(modifying_data[i]) <= frac)
			{
				modifying_data[i] = 0.0;
				++zeroes;
			}
		}
		std::cout << "COMPRESSED:" << std::endl
				  << modifying_data << std::endl;

		/* REDO TRANSFORMATION */
		transformator.apply_backward(modifying_data);
		thresh = 0.0;
		for (size_t i = 0; i < num; ++i)
		{
			tmp = std::abs(modifying_data[i] - initial_data[i]);
			if (tmp > thresh)
				thresh = tmp;
		}
		std::cout << "DECODED:" << std::endl
				  << modifying_data << std::endl;

		std::cout << "k, data len, zeroes = " << k << ' ' << num << ' ' << zeroes << std::endl
				  << "compressed difference = " << thresh << std::endl;
	}

	return 0;
}
