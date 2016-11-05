#include "component.hpp"


#include <sstream>
#include <iomanip>
#include <logger.hpp>


logger_t modulesLogger = loggerModule(Logger::Level::WARNING, loggerDescriptionFull);


size_t Component::_globID = 0;
size_t Component::_objectID = 0;
size_t Component::_shaderID = 0;
size_t Component::_materialID = 0;
size_t Component::_textureID = 0;
size_t Component::_sceneID = 0;
size_t Component::_guiID = 0;


Component::Component(const Component::Type& t,
					 const std::string& name)
	: _type(t),
	  _ID(++_globID),
	  _name(name)
{
	if (_name.empty())
		_name = _generateNameFromType(_type);

	logDebug << (*this) << " created" << logEndl;
}


Component::Component(const Component& c)
	: _type(c._type),
	  _ID(c._ID),
	  _name(c._name)
{
	logDebug << (*this) << " copied from " << c << logEndl;
}


Component::Component(Component&& c)
	: _type(std::move(c._type)),
	  _ID(std::move(c._ID)),
	  _name(std::move(c._name))
{
	logDebug << "Component " << (*this) << " moved" << logEndl;
}


Component::~Component()
{
	logDebug << "Component " << (*this) << " deleted" << logEndl;
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
	c._ID = ++_globID;
	c._name = _generateNameFromCopy(c);

	return std::move(c);
}


std::string Component::toString() const
{
	std::stringstream ss;
	ss << _name;
	return std::move(ss.str());
}


std::ostream& operator<<(std::ostream& out, const Component& c)
{
	out << "<Component:"
		<< &c << " '"
		<< c._name << "'>";

	return out;
}


std::string Component::_generateNameFromType(const Type& type)
{
	size_t id;
	std::stringstream ss;
	switch (type)
	{
		case Type::GUI:
			id = _guiID++;
			ss << "GUI";
			break;
		case Type::SCENE:
			id = _sceneID++;
			ss << "Scene";
			break;
		case Type::OBJECT:
			id = _objectID++;
			ss << "Object";
			break;
		case Type::MATERIAL:
			id = _materialID++;
			ss << "Material";
			break;
		case Type::TEXTURE:
			id = _textureID++;
			ss << "Texture";
			break;
		case Type::SHADER:
			id = _shaderID++;
			ss << "Shader";
			break;

		default:
			break;
	}

	ss << std::setw(3) << std::setfill('0') << id;

	return ss.str();
}


std::string Component::_generateNameFromCopy(const Component& c)
{
	std::stringstream ss;
	ss << c.getName() << ".copy";
	return ss.str();
}
