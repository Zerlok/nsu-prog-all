#ifndef __FILTERITERATOR_H__
#define __FILTERITERATOR_H__


#include <iterator>


template<class IteratorCls, class PredicateCls>
class FilterIterator
{
	public:
		typedef IteratorCls Iterator;
		typedef PredicateCls Predicate;

		typedef typename std::iterator_traits<Iterator>::value_type value_type;
		typedef typename std::iterator_traits<Iterator>::pointer pointer;
		typedef typename std::iterator_traits<Iterator>::reference reference;
		typedef typename std::iterator_traits<Iterator>::iterator_category iterator_category;

		FilterIterator() {}
		FilterIterator(
				const Iterator& it,
				const Iterator& end = Iterator(),
				const Predicate& pred = Predicate())
			: _curr(it),
			  _end(end),
			  _pred(pred)
		{
			if (!is_predicate())
				this->operator++();
		}
		FilterIterator(const FilterIterator<Iterator, Predicate>& iterator)
			: _curr(iterator._curr),
			  _end(iterator._end),
			  _pred(iterator._pred) {}
		FilterIterator(FilterIterator<Iterator, Predicate>&& iterator)
			: _curr(std::move(iterator._curr)),
			  _end(std::move(iterator._end)),
			  _pred(std::move(iterator._pred)) {}
		~FilterIterator() {}

		const Predicate& get_predicate() const
		{
			return _pred;
		}

		bool is_predicate() const
		{
			return _pred(*_curr);
		}

		bool operator==(const FilterIterator& iterator) const
		{
			return (_curr == iterator._curr);
		}

		bool operator!=(const FilterIterator& iterator) const
		{
			return (_curr != iterator._curr);
		}

		bool operator==(const Iterator& it) const
		{
			return (_curr == it);
		}

		bool operator!=(const Iterator& it) const
		{
			return (_curr != it);
		}

		FilterIterator& operator=(const typename Iterator::value_type& v)
		{
			_curr = v;
			return (*this);
		}

		FilterIterator& operator=(const FilterIterator& iterator)
		{
			_curr = iterator._curr;
			_end = iterator._end;
			_pred = iterator._pred;

			return (*this);
		}

		reference operator*()
		{
			return _curr.operator*();
		}

		pointer operator->()
		{
			return _curr.operator->();
		}

		FilterIterator& operator++()
		{
			if (_curr == _end)
				return (*this);

			do
				++_curr;
			while ((_curr != _end)
				   && !is_predicate());

			return (*this);
		}

	private:
		Iterator _curr;
		Iterator _end;
		Predicate _pred;
};


template<class IteratorCls, class PredicateCls>
FilterIterator<IteratorCls, PredicateCls> make_filter_iterator(
		const IteratorCls& it,
		const IteratorCls& end = IteratorCls(),
		const PredicateCls& pred = PredicateCls())
{
	return std::move(FilterIterator<IteratorCls, PredicateCls>(it, end, pred));
}


// __FILTERITERATOR_H__
#endif
