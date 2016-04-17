#include <algorithm>
#include <iterator>

#include "component.h"


static const std::string empty = "";


// ----------------- COMPONENT ----------------- //

Component& Component::endl(Component& c)
{
	c._push_line_end();
	return c;
}


Component&Component::operator<<(const bool& b)
{
	static const std::string str_true = "true";
	static const std::string str_false = "false";

	push_string(b ? str_true : str_false);
	return (*this);
}


Component& Component::operator<<(const std::string& s)
{
	push_string(s);
	return (*this);
}


Component& Component::operator<<(Component::manipulator_func_ptr manipulator)
{
	return manipulator(*this);
}


Component&Component::operator>>(std::string& s)
{
	s = get_string();
	return (*this);
}


// ----------------- STRING COMPONENT ----------------- //

StringComponent::StringComponent(const std::string &s)
	: Component(true, false),
	  _data(s)
{
}


std::string StringComponent::get_string()
{
	_is_clear = false;
	_is_ended = true;

	return _data;
}


void StringComponent::push_string(const std::string& s)
{
	_buffer << s;
}


bool StringComponent::update()
{
	_is_clear = true;
	_is_ended = false;

	_data = _buffer.str();

	_buffer.str(empty);
	_buffer.clear();

	return true;
}


void StringComponent::_push_line_end()
{
	_buffer << std::endl;
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

	_next_string = sc._next_string;

	return (*this);
}


std::string StreamComponent::get_string()
{
	std::string current_string;

	if (!_is_clear) // not the first call.
	{
		current_string = _next_string;
	}
	else // first call.
	{
		_is_clear = false;
		std::getline(_stream, current_string);
	}

	std::getline(_stream, _next_string);
	if (_stream.eof())
		_is_ended = true;

	return std::move(current_string);
}


void StreamComponent::push_string(const std::string& s)
{
	_buffer << s;
}


bool StreamComponent::update()
{
	if (!_is_ended)
		return false;

	_stream.swap(_buffer);
	_buffer.str(empty);
	_buffer.clear();

	_is_clear = true;
	_is_ended = false;

	return true;
}


void StreamComponent::_push_line_end()
{
	_buffer << std::endl;
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


std::string LinearComponent::get_string()
{
	if (_idx == 0)
		_is_clear = false;

	++_idx;
	if (_idx == _lines.size())
		_is_ended = true;

	return _lines[_idx - 1];
}


void LinearComponent::push_string(const std::string& s)
{
	_lines[_idx] = s;
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


void LinearComponent::_push_line_end()
{
	_lines.insert((_lines.begin() + _idx), empty);
	++_idx;
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
