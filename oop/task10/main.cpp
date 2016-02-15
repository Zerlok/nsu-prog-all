#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "filteriterator.h"


class Greater
{
	public:
		Greater(const int val = 0)
			: _val(val) {}
		bool operator()(int x) const { return x > _val; }

	private:
		const int _val;
};


int main()
{
	std::vector<int> values = {0, 1, 2, -4, 4, -1, -2, -4, 3};

	std::vector<int> vRes;

//	std::copy(
//				make_filter_iterator(values.begin(), values.end(), Greater()),
//				make_filter_iterator(values.end(), values.end(), Greater()),
//				std::back_inserter(vRes)
//				);

//	std::copy(
//			make_filter_iterator(values.begin(), values.end(), Greater()),
//			make_filter_iterator(values.end(), values.end(), Greater()),
//			std::ostream_iterator<int>(std::cout, ", ")
//	);

	std::cout << std::endl;

	return 0;
}
