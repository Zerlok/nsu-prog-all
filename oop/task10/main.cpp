#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "filteriterator.h"


class Pred
{
	public:
		bool operator()(int x) const { return x > 0; }
};


int main()
{
	std::vector<int> numbers = {0, 1, 2, -4, 4, -1, -2, -4};
	std::vector<int> filtered;

	std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, ", "));
	std::cout << std::endl;

	for (auto it = FilterIterator<std::vector<int>::iterator, Pred>(numbers.begin(), numbers.end(), Pred());
		 it != numbers.end();
		 ++it)
		filtered.push_back(*it);

	std::copy(filtered.begin(), filtered.end(), std::ostream_iterator<int>(std::cout, ", "));
	std::cout << std::endl;

	return 0;
}
