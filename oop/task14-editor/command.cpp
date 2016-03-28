#include <algorithm>
#include <stdexcept>
#include <sstream>
#include "command.h"


Command::Command(const Type& type, bool is_modif)
	: _type(type)
{
}


const Command::Type::Names& Command::Type::get_types_names()
{
	return _names;
}


const Command::Type::Types& Command::Type::get_types()
{
	return _types;
}


size_t Command::Type::index_of(const std::string& name)
{
	Names::iterator begin = _names.begin();
	return (std::find(begin, _names.end(), name) - begin);
}


size_t Command::Type::index_of(const Type &type)
{
	Names::iterator begin = _types.begin();
	return (std::find(begin, _types.end(), type) - begin);
}


const Command::Type& Command::Type::registrate(const std::string& name)
{
	_names.push_back(name);
	_types.push_back(Type(name));

	return _types.back();
}


const Command::Type& Command::Type::get(const std::string& name)
{
	return _types[index_of(name)];
}


const Command::Type& Command::Type::get(const size_t& idx)
{
	return _types[idx];
}


Command::Type::Type(const Command::Type& type)
	: _name(type._name)
{
}


Command::Type& Command::Type::operator=(const Command::Type& type)
{
	_name = type._name;
	return (*this);
}


void Command::Type::registrate(const size_t& idx, const std::string& name)
{
	Type t(name);

	if (idx >= _names.size())
	{
		_names.resize(idx+1);
		_types.resize(idx+1);
		_names[idx] = name;
		_types[idx] = t;
	}
	else
	{
		_names.insert(idx, name);
		_types.insert(idx, t);
	}

	return t;
}


Command::Type::Type(const std::string& name)
	: _name(name)
{
}


const std::string& Command::Type::get_name() const
{
	return _name;
}


size_t Command::Type::get_index() const
{
	return index_of(_name);
}


std::ostream operator<<(std::ostream& out, const Command::Type& type)
{
	return out << "[" << type._name << "]";
}


std::istream operator>>(std::istream& in, Command::Type& type)
{
	char ch = '';
	std::stringstream ss;

	in.ignore(1);
	while ((in >> ch)
		   && (ch != ']'))
		ss << ch;

	type = Command::Type::get(ss.str());

	return in;
}
