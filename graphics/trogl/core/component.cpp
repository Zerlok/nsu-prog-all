#include "component.hpp"


#include <iomanip>
#include <sstream>
#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


size_t Component::_globID = 0;
Component::Types Component::_types = {
	{"TEXTURE", 0},
	{"SHADER", 0},
	{"MATERIAL", 0},
	{"MESH", 0},
	{"LIGHT", 0},
	{"CAMERA", 0},
	{"ANIMATION", 0},
	{"FRAME", 0},
	{"SCENE", 0},
	{"GUI", 0},
};
std::hash<Component::Type> Component::_typeHash;
std::hash<size_t> Component::_idHash;


Component::Component(const Component::Type& type,
					 const std::string& name)
	: _type(type),
	  _id(_createIdFor(_type)),
	  _name(name)
{
	++_globID;
	_renameIfEmptyName(_name, _type);
	logDebug << (*this) << " created." << logEndl;
}


Component::Component(const Component& c)
	: _type(c._type),
	  _id(_createIdFor(_type)),
	  _name(_nextNumberOf(c._name))
{
	++_globID;
	logDebug << (*this) << " copied from " << c << logEndl;
}


Component::Component(Component&& c)
	: _type(std::move(c._type)),
	  _id(std::move(c._id)),
	  _name(std::move(c._name))
{
	logDebug << (*this) << " moved." << logEndl;
}


Component::~Component()
{
	logDebug << (*this) << " removed." << logEndl;
}


bool Component::sameType(const Component& c) const
{
	return (_type == c._type);
}


bool Component::sameType(Component&& c) const
{
	return (_type == c._type);
}


const size_t& Component::getId() const
{
	return _id;
}


const Component::Type& Component::getType() const
{	
	return _type;
}


const std::string& Component::getName() const
{
	return _name;
}


size_t Component::getHash() const
{
	size_t typeHash = _typeHash(_type);
	size_t idHash = _idHash(_id);
	return (typeHash ^ (idHash << 1));
}


void Component::rename(const std::string& name)
{
	_name = name;
}


std::string Component::toString() const
{
	return getName();
}


const size_t& Component::_createIdFor(const Component::Type& type)
{
	Types::iterator it = _types.find(type);
	if (it == _types.cend())
	{
		logWarning << "Unknown component type: " << type << logEndl;
		return ++_types["Undefined"];
	}

	return ++(it->second);
}


std::string Component::_nextNumberOf(const std::string& name)
{
	size_t pos = name.find('.');
	if (pos == std::string::npos)
		return _nameWithId(name, 1);

	size_t idx;
	std::stringstream ss;
	ss << name.substr(pos+1, name.length() - pos - 1);
	ss >> idx;

	return _nameWithId(name.substr(0, pos+1), idx+1);
}


std::string Component::_nameWithId(const std::string& name, const size_t& id)
{
	std::stringstream ss;
	ss << name << std::setw(3) << std::setfill('0') << id;
	return ss.str();
}


void Component::_renameIfEmptyName(const Component::Type& type, std::string& name)
{
	if (name.empty())
		name = _nameWithId(name, _types[type]);
}


std::ostream& operator<<(std::ostream& out, const Component& c)
{
	out << "<c-" << std::uppercase << c._type
		<< " #" << std::setw(4) << std::setfill('0') << c._id
		<< " '" << c._name << "'>";
	return out;
}


size_t Component::Hash::operator()(const Component& c) const
{
	return c.getHash();
}
