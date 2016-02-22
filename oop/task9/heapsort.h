#ifndef __HEAPSORT_H__
#define __HEAPSORT_H__


#include <iterator>
#include <vector>


class Less
{
	public:
		template<class T>
		bool operator()(const T& val1, const T& val2) const
		{
			return (val1 < val2);
		}
};


template<class Container, class Comparator>
void shift_down(
		Container& values,
		int root,
		int end,
		const Comparator& comparator)
{
	typedef typename Container::value_type container_value_t;
	container_value_t max_child;
	bool is_done = false;

	while ((root * 2 + 1 < end)
		   && (!is_done))
	{
		if (root * 2 + 1 == end - 1)
			max_child = root * 2 + 1;
		else if (comparator(values[root * 2 + 1], values[root * 2 + 2]))
			max_child = root * 2 + 2;
		else
			max_child = root * 2 + 1;

		if (comparator(values[root], values[max_child]))
		{
			std::swap(values[root], values[max_child]);
			root = max_child;
		}
		else
			is_done = true;
	}
}


template<class Container, class Comparator=Less >
void heap_sort(Container& values, const Comparator& comparator = Comparator())
{
	int root;
	int size = values.size();

	for (root = size / 2 - 1;
		 root >= 0;
		 --root)
		shift_down(values, root, size, comparator);

	for (root = size - 1;
		 root >= 1;
		 --root)
	{
		std::swap(values[0], values[root]);
		shift_down(values, 0, root, comparator);
	}
}


// __HEAPSORT_H__
#endif
