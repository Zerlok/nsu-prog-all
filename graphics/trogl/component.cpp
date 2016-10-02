#include "component.hpp"

#include <logger.hpp>
#include <sstream>
#include <iomanip>


size_t Component::globID = 0;


std::string Component::generateNameFromType(const Type& type, const size_t& id)
{
	std::stringstream ss;
	switch (type)
	{
		case Type::GUI:
			ss << "GUI";
			break;
		case Type::SCENE:
			ss << "Scene";
			break;
		case Type::OBJECT:
			ss << "Object";
			break;
		case Type::MATERIAL:
			ss << "Material";
			break;
		case Type::TEXTURE:
			ss << "Texture";
			break;
		default:
			break;
	}

	ss << std::setw(3) << std::setfill('0') << id;

	return ss.str();
}


std::string Component::generateNameFromCopy(const Component& c)
{
	std::stringstream ss;
	ss << c.getName() << ".copy";
	return ss.str();
}


Component::Component(const Component::Type& t,
					 const std::string& name)
	: _type(t),
	  _ID(++globID),
	  _name(name)
{
	if (_name.empty())
		_name = generateNameFromType(_type, _ID);

	logDebug << (*this) << " created" << logEnd;
}


Component::Component(const Component& c)
	: _type(c._type),
	  _ID(c._ID),
	  _name(c._name)
{
	logDebug << (*this) << " created from " << c << logEnd;
}


Component::Component(Component&& c)
	: _type(std::move(c._type)),
	  _ID(std::move(c._ID)),
	  _name(std::move(c._name))
{
	logDebug << "Component " << (*this) << " moved" << logEnd;
}


Component::~Component()
{
	logDebug << "Component " << (*this) << " deleted" << logEnd;
}


Component& Component::operator=(const Component& c)
{
	_type = c._type;
	_ID = c._ID;
	_name = c._name;

	return (*this);
}


Component& Component::operator=(Component&& c)
{
	_type = std::move(c._type);
	_ID = std::move(c._ID);
	_name = std::move(c._name);

	return (*this);
}


bool Component::operator==(const Component& c) const
{
	return (_ID == c._ID);
}


bool Component::operator!=(const Component& c) const
{
	return (!this->operator==(c));
}


const Component::Type& Component::getType() const
{	
	return _type;
}


const std::string& Component::getName() const
{
	return _name;
}


void Component::setName(const std::string& name)
{
	_name = name;
}


Component Component::copy() const
{
	Component c(*this);
	c._ID = ++globID;
	c._name = generateNameFromCopy(c);

	return std::move(c);
}


std::ostream&operator<<(std::ostream& out, const Component& c)
{
	out << "<Component:"
		<< &c << " '"
		<< c._name << "'>";

	return out;
}
