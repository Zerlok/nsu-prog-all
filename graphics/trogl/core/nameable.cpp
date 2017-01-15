#include "nameable.hpp"


#include <iomanip>
#include <sstream>


Nameable::Nameable(const std::string& name)
	: _name(name)
{
	_renameIfEmptyName(_name);
}


Nameable::Nameable(const Nameable& n)
	: _name(_nextNumberOf(n._name))
{
}


Nameable::Nameable(Nameable&& n)
	: _name(std::move(n._name))
{
}


Nameable::~Nameable()
{
}


Nameable& Nameable::operator=(const Nameable& n)
{
	_name = n._name;
	return (*this);
}


Nameable& Nameable::operator=(Nameable&& n)
{
	_name = std::move(n._name);
	return (*this);
}


const std::string& Nameable::getName() const
{
	return _name;
}


void Nameable::rename(const std::string& name)
{
	_name = name;
}


void Nameable::renameWithId(const std::string& name, const size_t& id)
{
	_name = _nameWithId(name, id);
}


std::string Nameable::_nextNumberOf(const std::string& name)
{
	size_t pos = name.find('.');
	if (pos == std::string::npos)
	{
		std::string tmp(name);
		_appendWithNumber(tmp);
		return std::move(tmp);
	}

	size_t idx;
	std::stringstream ss;
	ss << name.substr(pos+1, name.length() - pos - 1);
	ss >> idx;

	return _nameWithId(name.substr(0, pos+1), idx+1);
}


std::string Nameable::_nameWithId(const std::string& name, const size_t& id)
{
	std::stringstream ss;
	ss << name << std::setw(3) << std::setfill('0') << id;
	return ss.str();
}


void Nameable::_appendWithNumber(std::string& name)
{
	name = _nameWithId(name, 1);
}


void Nameable::_renameIfEmptyName(std::string& name)
{
	if (name.empty())
	{
		name = "Unnamed";
		_appendWithNumber(name);
	}
}


std::ostream& operator<<(std::ostream& out, const Nameable& n)
{
	return out << '\'' << n.getName() << '\'';
}
