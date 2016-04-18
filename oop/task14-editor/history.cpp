#include "history.h"


History::History()
	: _index(0), _data_queue()
{
}


const std::string& History::get_current() const
{
	return _data_queue[_index];
}


void History::push_back(const std::string& data)
{
	const size_t& size = _data_queue.size();
	if ((size != 0)
			&& (_index < size - 1))
		_remove_after(_index);

	if (!_data_queue.empty())
		++_index;

	_data_queue.push_back(data);
}


bool History::has_next() const
{
	return (_index + 1 < _data_queue.size());
}


bool History::has_previous() const
{
	return (_index >= 1);
}


const std::string& History::next()
{
	if (!has_next())
		return get_current();

	++_index;
	return get_current();
}


const std::string& History::previous()
{
	if (!has_previous())
		return get_current();

	--_index;
	return get_current();
}


void History::_remove_after(const size_t& index)
{
	for (size_t i = _data_queue.size() - 1; i > index; --i)
		_data_queue.pop_back();
}


