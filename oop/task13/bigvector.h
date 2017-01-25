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
		BigVector(
				std::iostream& dump_stream,
				const size_t& window_width			= DEFAULT_WINDOW_SIZE
		);
		BigVector(const BigVector&) = delete;
		BigVector(BigVector&& vector);
		~BigVector();

		// Operators.
		BigVector& operator=(const BigVector&) = delete;
		BigVector& operator=(BigVector&& vector);

		const Type& operator[](const size_t& idx) const;
		Type& operator[](const size_t& idx);

		// Getters.
		size_t size() const;

		const_iterator cbegin() const;
		const_iterator cend() const;

		const_iterator begin() const;
		const_iterator end() const;

		iterator begin();
		iterator end();

		const Type& cget(const size_t& idx) const;
		const Type& get(const size_t& idx) const;
		Type& get(const size_t& idx);

		// Methods.
		void flush() const;

		Type pop_back();

		void push_back(const Type& obj);
		void push_back(Type&& obj);

	private:
		// Fields.
		mutable std::iostream _dump_stream;
		mutable size_t _dump_size;

		size_t _total_size;
		mutable size_t _window_offset;
		size_t _window_width;
		mutable std::vector<Type> _data_window;
		mutable bool _is_dirty_window;

		// Getters.
		size_t _count_window_offset(const size_t& idx) const;
		size_t _count_max_window_pos() const;

		bool _is_in_window(const size_t& idx) const;

		// Methods.
		void _update_data_window(const size_t& pos) const;
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
BigVector<T>::BigVector(std::iostream& dump_stream, const size_t& window_width)
	: _dump_stream(dump_stream),
	  _dump_size(0),
	  _total_size(0),
	  _window_offset(0),
	  _window_width(window_width),
	  _data_window(0),
	  _is_dirty_window(false)
{
	/*
	 * IF stream is not empty
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
	flush();
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
	return get(idx);
}


template<class T>
const T& BigVector<T>::operator[](const size_t& idx) const
{
	return cget(idx);
}


template<class T>
size_t BigVector<T>::size() const
{
	return _total_size;
}


template<class T>
typename BigVector<T>::const_iterator BigVector<T>::cbegin() const
{
	return std::move(const_iterator(this, 0));
}


template<class T>
typename BigVector<T>::const_iterator BigVector<T>::cend() const
{
	return std::move(const_iterator(this, _total_size));
}


template<class T>
typename BigVector<T>::const_iterator BigVector<T>::begin() const
{
	return cbegin();
}


template<class T>
typename BigVector<T>::const_iterator BigVector<T>::end() const
{
	return cend();
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
const T& BigVector<T>::cget(const size_t& idx) const
{
	if (!_is_in_window(idx))
	{
		flush();
		_update_data_window(_count_window_offset(idx));
	}

	return _data_window[(idx - _window_offset)];
}


template<class T>
const T& BigVector<T>::get(const size_t& idx) const
{
	return cget(idx);
}


template<class T>
T& BigVector<T>::get(const size_t& idx)
{
	if (!_is_in_window(idx))
	{
		flush();
		_update_data_window(_count_window_offset(idx));
	}

	_is_dirty_window = true;
	return _data_window[(idx - _window_offset)];
}


template<class T>
void BigVector<T>::flush() const
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
T BigVector<T>::pop_back()
{
	/*
	 * IF current window is not viewing the end of vector
	 * OR window is empty
	 * THAN save current window and load the last window (at the end).
	 */
	if ((_window_offset < _dump_size)
			|| (_data_window.empty()))
	{
		flush();
		_window_offset = _count_window_offset(_total_size);
		_data_window.clear();
	}

	T tmp = _data_window.back();

	--_total_size;
	_data_window.pop_back();
	_is_dirty_window = true;

	return std::move(tmp);
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
		flush();
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
		flush();
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
void BigVector<T>::_update_data_window(const size_t& pos) const
{
	if (_is_dirty_window
			|| (_dump_size == 0))
		return;

	_window_offset = pos;
	_data_window.clear();

	T tmp {};
	_dump_stream.seekg(_window_offset * sizeof(T) + sizeof(size_t));
	for (size_t i = 0; i < _window_width; ++i)
	{
		deserialize(_dump_stream, tmp);
		_data_window.push_back(tmp);
	}
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
			  _offset(offset) { }
		iterator(const iterator& it)
			: _container(it._container),
			  _offset(it._offset) { }
		iterator(iterator&& it)
			: _container(it._container),
			  _offset(std::move(it._offset))
		{
			it._container = nullptr;
			it._offset = 0;
		}
		~iterator() { }

		// Operators.
		bool operator==(const iterator& it) const
		{
			return (_offset == it._offset);
		}
		bool operator!=(const iterator& it) const
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

			return std::move(tmp);
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

			return std::move(tmp);
		}

		iterator operator+(const size_t& x)
		{
			iterator tmp(*this);
			tmp._offset += x;

			return std::move(tmp);
		}
		iterator operator-(const size_t& x)
		{
			iterator tmp(*this);
			tmp._offset -= x;

			return std::move(tmp);
		}

		T& operator*()
		{
			return _container->get(_offset);
		}
		T* operator->()
		{
			return &(_container->get(_offset));
		}

	private:
		BigVector<T>* _container;
		size_t _offset;
};


template<class T>
class BigVector<T>::const_iterator
{
	public:
		// Typedefs.
		typedef typename std::vector<T>::const_iterator						Iterator;
		typedef typename std::iterator_traits<Iterator>::value_type			value_type;
		typedef typename std::iterator_traits<Iterator>::pointer			pointer;
		typedef typename std::iterator_traits<Iterator>::reference			reference;
		typedef typename std::iterator_traits<Iterator>::difference_type	difference_type;
		typedef std::random_access_iterator_tag								iterator_category;

		// Constructors / Destructor.
		const_iterator(const BigVector<T>* container, const size_t& offset)
			: _container(container),
			  _offset(offset) { }
		const_iterator(const const_iterator& it)
			: _container(it._container),
			  _offset(it._offset) { }
		const_iterator(const_iterator&& it)
			: _container(it._container),
			  _offset(std::move(it._offset))
		{
			it._container = nullptr;
			it._offset = 0;
		}
		~const_iterator() { }

		// Operators.
		bool operator==(const const_iterator& it) const
		{
			return (_offset == it._offset);
		}
		bool operator!=(const const_iterator& it) const
		{
			return !(this->operator==(it));
		}

		const_iterator& operator++()
		{
			++_offset;
			return (*this);
		}
		const_iterator operator++(int)
		{
			const_iterator tmp(*this);
			this->operator++();

			return std::move(tmp);
		}

		const_iterator& operator--()
		{
			--_offset;
			return (*this);
		}
		const_iterator operator--(int)
		{
			const_iterator tmp(*this);
			this->operator--();

			return std::move(tmp);
		}

		const_iterator operator+(const size_t& x)
		{
			const_iterator tmp(*this);
			tmp._offset += x;

			return std::move(tmp);
		}
		const_iterator operator-(const size_t& x)
		{
			const_iterator tmp(*this);
			tmp._offset -= x;

			return std::move(tmp);
		}

		const T& operator*() const
		{
			return _container->cget(_offset);
		}
		const T* operator->() const
		{
			return &(_container->cget(_offset));
		}

	private:
		const BigVector<T>* _container;
		size_t _offset;
};


// __BIGVECTOR_H__
#endif
