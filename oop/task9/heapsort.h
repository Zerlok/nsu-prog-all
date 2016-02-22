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


template<class Iterator, class Comparator>
void shift_down(
		const Iterator& begin,
		Iterator it,
		const Iterator& end,
		const Comparator& comparator)
{
	Iterator pre_last = end - 1;
	Iterator root = begin + ((it - begin) * 2);
	Iterator left_child;
	Iterator right_child;
	Iterator max_child;
	bool is_done = false;

	while (((root + 1) <= pre_last)
		   && (!is_done))
	{
		left_child = root + 1;
		right_child = left_child + 1;

		if (left_child == pre_last)
			max_child = left_child;
		else if (comparator(*left_child, *right_child))
			max_child = right_child;
		else
			max_child = left_child;

		if (comparator(*it, *max_child))
		{
			std::swap(*it, *max_child);
			it = max_child;
			root = begin + ((it - begin) * 2);
		}
		else
			is_done = true;
	}
}


template<class Iterator, class Comparator=Less >
void heap_sort(
		const Iterator& begin,
		const Iterator& end,
		const Comparator& comparator = Comparator())
{
	typedef typename std::iterator_traits<Iterator>::difference_type diff_t;
	diff_t size = (end - begin);

	if (size <= 1)
		return;

	for (Iterator root = begin + (size / 2 - 1);
		 root != begin;
		 --root)
		shift_down(begin, root, end, comparator);

	shift_down(begin, begin, end, comparator);

	for (Iterator it = begin + (size - 1);
		 it != begin;
		 --it)
	{
		std::swap(*begin, *it);
		shift_down(begin, begin, it, comparator);
	}
}


// __HEAPSORT_H__
#endif
