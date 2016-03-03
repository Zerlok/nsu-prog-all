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
		// Typedefs.

		// Classes.
		class iterator;
		class const_iterator;

		// Constructors / Destructor.
		BigVector(
				const std::string& dump_filename = DEFAULT_DUMP_FILENAME,
				const size_t window_width = DEFAULT_WINDOW_SIZE
		);
		BigVector(const BigVector& vector) = delete;
		BigVector(BigVector&& vector);
		~BigVector();

		// Operators.
		BigVector& operator=(const BigVector& vector) = delete;
		BigVector& operator=(BigVector&& vector);

		Type& operator[](const size_t idx);
		const Type& operator[](const size_t idx) const;

		// Methods.

	private:
		// Fields.
		std::fstream _dump_stream;
		size_t _window_pos; // window offset from the begining of the file.
		size_t _window_width; // amount of Type in window.
		std::vector<Type> _data_window;
		bool _is_dirty_window;

		// Methods.
		bool _is_in_window(const size_t idx) const;
		size_t _get_window_pos_from_index(const size_t idx) const;
		void _read_data_window(const size_t pos);
		void _write_data_window();
};


template<class T>
BigVector<T>::BigVector(const std::string& dump_filename, const size_t window_width)
	: _dump_stream(dump_filename, std::ios::in | std::ios::out | std::ios::binary),
	  _window_pos(0),
	  _window_width(window_width),
	  _data_window(0),
	  _is_dirty_window(false)
{
}


template<class T>
T& BigVector<T>::operator[](const size_t idx)
{
	if (!_is_in_window(idx))
	{
		if (_is_dirty_window)
			_write_data_window();

		_read_data_window(_get_window_pos_from_index(idx));
	}

	_is_dirty_window = true;
	return _data_window[(idx - _window_pos)];
}


template<class T>
const T& BigVector<T>::operator[](const size_t idx) const
{
	// TODO: solve conflict with reading data (not const method) if idx is out of window range.
	return _data_window[(idx - _window_pos)];
}


template<class T>
bool BigVector<T>::_is_in_window(const size_t idx) const
{
	return ((_window_pos <= idx)
			&& (idx < (_window_pos + _data_window.size())));
}


template<class T>
size_t BigVector<T>::_get_window_pos_from_index(const size_t idx) const
{
	// TODO: check for right border outgoing (requires total elemnts amount).
	const size_t half = _window_width / 2;
	return (idx > half)
			? (idx - half)
			: 0;
}


template<class T>
void BigVector<T>::_read_data_window(const size_t pos)
{
	T tmp {};
	_data_window.clear();
	_is_dirty_window = false;
	_dump_stream.seekg(pos * sizeof(T));

	while ((_data_window.size() < _window_width)
		   && _dump_stream)
	{
		deserialize<T>(_dump_stream, tmp);
		_data_window.push_back(tmp);
	}
}


template<class T>
void BigVector<T>::_write_data_window()
{
	_is_dirty_window = false;
	_dump_stream.seekp(pos * sizeof(T));

	for (const T& data : _data_window)
		serialize<T>(_dump_stream, data);
}


// __BIGVECTOR_H__
#endif
