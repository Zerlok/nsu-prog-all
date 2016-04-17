#include <algorithm>
#include <iterator>

#include "component.h"


// ----------------- STRING COMPONENT ----------------- //

StringComponent::StringComponent(const std::string &s)
	: Component(true, false),
	  _data(s)
{
}


std::string& StringComponent::get_string()
{
	_is_clear = false;
	_is_ended = true;

	return _data;
}


bool StringComponent::update()
{
	_is_clear = true;
	_is_ended = false;

	return true;
}


std::istream& operator>>(std::istream& in, StringComponent& sc)
{
	std::getline(in, sc._data);
	sc._is_clear = true;
	sc._is_ended = false;

	return in;
}


std::ostream& operator<<(std::ostream& out, const StringComponent& component)
{
	out << component._data << std::endl;

	return out;
}


// ----------------- STREAM COMPONENT ----------------- //

StreamComponent::StreamComponent(std::istream& in)
{
	in >> (*this);
}


StreamComponent& StreamComponent::operator=(const StreamComponent& sc)
{
	_stream.str(sc._stream.str());
	_buffer.str(sc._buffer.str());
	_stream.clear();
	_buffer.clear();

	_last_string = sc._last_string;
	_next_string = sc._next_string;

	return (*this);
}


std::string& StreamComponent::get_string()
{
	if (!_is_clear) // not the first call.
	{
		_buffer << _last_string << std::endl;
		_last_string = _next_string;
	}
	else // first call.
	{
		_is_clear = false;
		std::getline(_stream, _last_string);
	}

	std::getline(_stream, _next_string);
	if (_stream.eof())
		_is_ended = true;

	return _last_string;
}


bool StreamComponent::update()
{
	if (!_is_ended)
		return false;

	_buffer << _last_string << std::endl;

	_stream.swap(_buffer);
	_buffer.str("");
	_buffer.clear();

	_is_clear = true;
	_is_ended = false;

	return true;
}


StreamComponent& StreamComponent::operator<<(const std::string& s)
{
	_buffer << s;

	return (*this);
}


StreamComponent& StreamComponent::operator<<(StreamComponent::std_endl manipulator)
{
	manipulator(_buffer);

	return (*this);
}


std::istream& operator>>(std::istream& in, StreamComponent& sc)
{
	std::copy(
			std::istreambuf_iterator<char>(in),
			std::istreambuf_iterator<char>(),
			std::ostreambuf_iterator<char>(sc._stream));

	sc._is_ended = false;

	return in;
}


std::ostream& operator<<(std::ostream& out, const StreamComponent& component)
{
	std::string line;
	while (std::getline(component._stream, line))
		out << line << std::endl;

	return out;
}


// ----------------- LINEAR COMPONENT ----------------- //

LinearComponent::LinearComponent(std::istream& in)
	: Component(),
	  _idx(0)
{
	in >> (*this);
}


std::string& LinearComponent::get_string()
{
	if (_idx == 0)
		_is_clear = false;

	++_idx;
	if (_idx == _lines.size())
		_is_ended = true;

	return _lines[_idx - 1];
}


bool LinearComponent::update()
{
	if (!_is_ended)
		return false;

	_idx = 0;
	_is_clear = true;
	_is_ended = false;

	return true;
}


std::istream& operator>>(std::istream& in, LinearComponent& lc)
{
	std::string line;
	while (std::getline(in, line))
		lc._lines.push_back(line);

	lc._is_ended = false;

	return in;
}


std::ostream& operator<<(std::ostream& out, const LinearComponent& lc)
{
	for (const std::string& line : lc._lines)
		out << line << std::endl;

	return out;
}
