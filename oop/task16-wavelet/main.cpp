#ifdef _RELEASE_

#include <iostream>
#include <vector>
#include <cmath>

#include "transformators.h"
#include "haar.h"
#include "daub4.h"
#include "utils.h"

static const int NMAX = 512;
static const float RBEG = 0.25;
static const float REND = 0.75;
static const float bottom = 0.0;
static const float top = 1.0;
static const bool display = true;

using Doubles = std::vector<double>;


double get_k_min_abs_value(const std::vector<double>& vec, const size_t& k)
{
	std::vector<double> saved;

	for (size_t i = 0; i < vec.size(); ++i)
	{
		if (i >= k)
		{
			for (size_t j = 0; j < k; ++j)
				if (std::fabs(vec[i]) < saved[j])
					saved.insert(saved.begin()+j, std::abs(vec[i]));
		}
		else
			saved.push_back(vec[i]);
	}

	return saved[k];
}


int main(int argc, char *argv[])
{
	int k;
	bool invalid_k;
	float frac, thresh, tmp;
	size_t nbeg, nend, num;
	size_t zeroes;

	DividingTransformator<double> transformator;

	for (;;)
	{
		/* DATA READ BLOCK */
		std::cout << "Enter k [-2 - Haar, -4 - DAUB4]" << std::endl
				  << "compressing ratio (0.0 <= frac <= 1.0)" << std::endl
				  << "len of data (if 0 then 512):" << std::endl;
		std::cin >> k >> frac >> num;
		invalid_k = false;
		if (num == 0)
			num = NMAX;
		nbeg = RBEG * num;
		nend = REND * num;

		Doubles initial_data(num);
		Doubles encoded_data(num);
		Doubles compressed_data(num);
		Doubles decoded_data(num);

		frac = std::min(top, std::max(frac, bottom));
		/* SET TRANSFORMATION FROM K */
		switch (k)
		{
			case -2:
				transformator.set_transformation(new HaarTransformation<double>());
				break;

			case -4:
				transformator.set_transformation(new DAUB4Transform<double>());
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
				initial_data[i] = ((double(nend-i) * double(i-nbeg) * 4) / ((nend-nbeg)*(nend-nbeg)));
		if (display)
			std::cout << "INIT:" << std::endl
					  << initial_data << std::endl;

		/* DO TRANSFORMATION */
		encoded_data = transformator.apply_forward(initial_data);
		if (display)
			std::cout << "ENCODED:" << std::endl
					  << encoded_data << std::endl;

		/* DO COMPRESSING */
		zeroes = 0;
		const double k_min_value = get_k_min_abs_value(encoded_data, num * frac);
		for (size_t i = 0; i < num; ++i)
		{
			if (std::abs(encoded_data[i]) <= k_min_value)
			{
				compressed_data[i] = 0.0;
				++zeroes;
			}
			else
				compressed_data[i] = encoded_data[i];
		}
		if (display)
			std::cout << "COMPRESSED:" << std::endl
					  << compressed_data << std::endl;

		/* REDO TRANSFORMATION */
		decoded_data = transformator.apply_backward(compressed_data);
		thresh = 0.0;
		for (size_t i = 0; i < num; ++i)
		{
			tmp = std::abs(decoded_data[i] - initial_data[i]);
			if (tmp > thresh)
				thresh = tmp;
		}
		if (display)
			std::cout << "DECODED:" << std::endl
					  << decoded_data << std::endl;

		std::cout << "k, data len, additional zeroes = " << k << ' ' << num << ' ' << zeroes << std::endl
				  << "compressed difference = " << thresh << std::endl;
	}

	return 0;
}

#endif
