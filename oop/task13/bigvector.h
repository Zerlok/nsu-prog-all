#ifndef __BIGVECTOR_H__
#define __BIGVECTOR_H__


#include <ios>
#include <fstream>
#include <iterator>
#include <vector>
#include "serdeser.h"


static const std::string DEFAULT_DUMP_FILENAME	= "a.dump";
static const size_t DEFAULT_WINDOW_SIZE			= 1000;
static const std::ios::openmode dump_mode		= (std::ios::in | std::ios::out | std::ios::binary);


template<class Type>
class BigVector
{
	public:
		// Classes.
		class iterator;
		class const_iterator;

		// Constructors / Destructor.
		BigVector(
				const std::string& dump_filename	= DEFAULT_DUMP_FILENAME,
				const size_t& window_width			= DEFAULT_WINDOW_SIZE
		);
		BigVector(const BigVector&) = delete;
		BigVector(BigVector&& vector);
		~BigVector();

		// Operators.
		BigVector& operator=(const BigVector&) = delete;
		BigVector& operator=(BigVector&& vector);

		Type& operator[](const size_t& idx);
		const Type& operator[](const size_t& idx) const;

		// Getters.
		size_t size() const;

		iterator begin();
		iterator end();

		const_iterator begin() const;
		const_iterator end() const;
		const_iterator cbegin() const;
		const_iterator cend() const;

		// Methods.
		void push_back(Type&& obj);
		void push_back(const Type& obj);

	private:
		// Fields.
		std::fstream _dump_stream;
		size_t _dump_size;

		size_t _total_size;
		size_t _window_offset;
		size_t _window_width;
		std::vector<Type> _data_window;
		bool _is_dirty_window;

		// Getters.
		size_t _count_window_offset(const size_t& idx) const;
		size_t _count_max_window_pos() const;

		bool _is_in_window(const size_t& idx) const;

		// Methods.
		void _update_data_window(const size_t& pos);
		void _update_dumpfile();
		void _shift_data_window_right();
};


template<class T>
BigVector<T>::BigVector(const std::string& dump_filename, const size_t& window_width)
	: _dump_stream(dump_filename, dump_mode),
	  _dump_size(0),
	  _total_size(0),
	  _window_offset(0),
	  _window_width(window_width),
	  _data_window(0),
	  _is_dirty_window(false)
{
	// TODO: fix this stupid reopening.
	if (!_dump_stream.is_open())
	{
		// close current stream.
		_dump_stream.close();
		// create nonexistent file.
		std::ofstream ofs(dump_filename);
		// save it.
		ofs.close();
		// and open stream again.
		_dump_stream.open(dump_filename, dump_mode);
	}

	/*
	 * IF file is not empty
	 * THAN read the amount of elements in it.
	 */
	_dump_stream.seekg(0, std::ios::end);
	if (_dump_stream.tellg() > 0)
	{
		_dump_stream.seekg(0);
		deserialize(_dump_stream, _total_size);
		_dump_size = _total_size;
	}
}


template<class T>
BigVector<T>::BigVector(BigVector&& vector)
	: _dump_stream(std::move(vector._dump_stream)),
	  _dump_size(std::move(vector._dump_size)),
	  _total_size(std::move(vector._total_size)),
	  _window_offset(std::move(vector._window_offset)),
	  _window_width(std::move(vector._window_width)),
	  _data_window(std::move(vector._data_window)),
	  _is_dirty_window(std::move(vector._is_dirty_window))
{
}


template<class T>
BigVector<T>::~BigVector()
{
	_update_dumpfile();
	_dump_stream.close();
}


template<class T>
BigVector<T>& BigVector<T>::operator=(BigVector&& vector)
{
	_dump_stream = std::move(vector._dump_stream);
	_dump_size = std::move(vector._dump_size);
	_total_size = std::move(vector._total_size);
	_window_offset = std::move(vector._window_offset);
	_window_width = std::move(vector._window_width);
	_data_window = std::move(vector._data_window);
	_is_dirty_window = std::move(vector._is_dirty_window);

	return (*this);
}


template<class T>
T& BigVector<T>::operator[](const size_t& idx)
{
	if (!_is_in_window(idx))
	{
		_update_dumpfile();
		_update_data_window(_count_window_offset(idx));
	}

	_is_dirty_window = true;
	return _data_window[(idx - _window_offset)];
}


template<class T>
const T& BigVector<T>::operator[](const size_t& idx) const
{
	// TODO: solve conflict with reading data (not const method) if idx is out of window range.
	// _check_and_update_window(idx);
	return _data_window[(idx - _window_offset)];
}


template<class T>
size_t BigVector<T>::size() const
{
	return _total_size;
}


template<class T>
typename BigVector<T>::iterator BigVector<T>::begin()
{
	return std::move(iterator(this, 0));
}


template<class T>
typename BigVector<T>::iterator BigVector<T>::end()
{
	return std::move(iterator(this, _total_size));
}


template<class T>
void BigVector<T>::push_back(T&& obj)
{
	/*
	 * IF current window is not viewing the end of vector
	 * OR window size is expanding more than adjusted width
	 * THAN save current window and shift it to the end.
	 */
	if ((_window_offset < _dump_size)
			|| (_data_window.size() >= _window_width))
	{
		_update_dumpfile();
		_window_offset = _dump_size;
		_data_window.clear();
	}

	++_total_size;
	_data_window.push_back(obj);
	_is_dirty_window = true;
}


template<class T>
void BigVector<T>::push_back(const T& obj)
{
	/*
	 * IF current window is not viewing the end of vector
	 * OR window size is expanding more than adjusted width
	 * THAN save current window and shift it to the end.
	 */
	if ((_window_offset < _dump_size)
			|| (_data_window.size() >= _window_width))
	{
		_update_dumpfile();
		_window_offset = _dump_size;
		_data_window.clear();
	}

	++_total_size;
	_data_window.push_back(obj);
	_is_dirty_window = true;
}


template<class T>
size_t BigVector<T>::_count_window_offset(const size_t& idx) const
{
	const size_t half_window_size = _window_width / 2;

	// Count offset so the element at 'idx' position will be at center of the window.
	if (idx <= half_window_size)
		return 0;

	else if (idx >= (_dump_size - half_window_size))
		return (_dump_size - _window_width);

	else
		return (idx - half_window_size);
}


template<class T>
bool BigVector<T>::_is_in_window(const size_t& idx) const
{
	return ((_window_offset <= idx)
			&& (idx < (_window_offset + _data_window.size())));
}


template<class T>
void BigVector<T>::_update_data_window(const size_t& pos)
{
	if (_is_dirty_window
			|| (_dump_size == 0))
		return;

	_window_offset = pos;
	_data_window.clear();

	_dump_stream.seekg(_window_offset * sizeof(T) + sizeof(size_t));
	for (size_t i = 0; i < _window_width; ++i)
	{
		T tmp {};
		deserialize(_dump_stream, tmp);
		_data_window.push_back(tmp);
	}
}


template<class T>
void BigVector<T>::_update_dumpfile()
{
	if (!_is_dirty_window)
		return;

	_dump_stream.seekp(0);
	serialize(_dump_stream, _total_size);
	_dump_size = _total_size;

	_dump_stream.seekp(_window_offset * sizeof(T) + sizeof(size_t));
	for (size_t i = 0; i < _data_window.size(); ++i)
		serialize(_dump_stream, _data_window[i]);

	_is_dirty_window = false;
}


template<class T>
class BigVector<T>::iterator
{
	public:
		// Typedefs.
		typedef typename std::vector<T>::iterator							Iterator;
		typedef typename std::iterator_traits<Iterator>::value_type			value_type;
		typedef typename std::iterator_traits<Iterator>::pointer			pointer;
		typedef typename std::iterator_traits<Iterator>::reference			reference;
		typedef typename std::iterator_traits<Iterator>::difference_type	difference_type;
		typedef std::random_access_iterator_tag								iterator_category;

		// Constructors / Destructor.
		iterator(BigVector<T>* container, const size_t& offset)
			: _container(container),
			  _offset(offset) {}
		iterator(const iterator& it)
			: _container(it._container),
			  _offset(it._offset) {}
		iterator(iterator&& it)
			: _container(it._container),
			  _offset(it._offset) {}
		~iterator() {}

		// Operators.
		bool operator==(const iterator& it)
		{
			return (_offset == it._offset);
		}

		bool operator!=(const iterator& it)
		{
			return !(this->operator==(it));
		}

		iterator& operator++()
		{
			++_offset;
			return (*this);
		}

		iterator operator++(int)
		{
			iterator tmp(*this);
			this->operator++();

			return tmp;
		}

		iterator& operator--()
		{
			--_offset;
			return (*this);
		}

		iterator operator--(int)
		{
			iterator tmp(*this);
			this->operator--();

			return tmp;
		}

		iterator operator+(const size_t& x)
		{
			iterator tmp(*this);
			tmp._offset += x;

			return tmp;
		}

		iterator operator-(const size_t& x)
		{
			iterator tmp(*this);
			tmp._offset -= x;

			return tmp;
		}

		T& operator*()
		{
			return _container->operator[](_offset);
		}

		T* operator->()
		{
			return &(_container->operator[](_offset));
		}

	private:
		BigVector<T>* _container;
		size_t _offset;
};


template<class T>
class BigVector<T>::const_iterator
{
		// Typedefs.
		typedef typename std::vector<T>::const_iterator						Iterator;
		typedef typename std::iterator_traits<Iterator>::value_type			value_type;
		typedef typename std::iterator_traits<Iterator>::pointer			pointer;
		typedef typename std::iterator_traits<Iterator>::reference			reference;
		typedef typename std::iterator_traits<Iterator>::difference_type	difference_type;
		typedef std::forward_iterator_tag									iterator_category;
};


// __BIGVECTOR_H__
#endif
