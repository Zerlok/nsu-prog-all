#ifndef __BIGVECTOR_H__
#define __BIGVECTOR_H__


#include <ios>
#include <fstream>
#include <iterator>
#include <vector>
#include "serdeser.h"


static const std::string DEFAULT_DUMP_FILENAME = "a.dump";
static const size_t DEFAULT_WINDOW_SIZE = 1000;


template<class Type>
class BigVector
{
	public:
		// Classes.
		class iterator;
		class const_iterator;

		// Constructors / Destructor.
		BigVector(
				const std::string& dump_filename = DEFAULT_DUMP_FILENAME,
				const size_t& window_width = DEFAULT_WINDOW_SIZE
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
	: _dump_stream(dump_filename, std::ios::in | std::ios::out | std::ios::binary),
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
		_dump_stream.open(dump_filename, std::ios::in | std::ios::out | std::ios::binary);
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
BigVector<T>::~BigVector()
{
	_update_dumpfile();
	_dump_stream.close();
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


// __BIGVECTOR_H__
#endif
