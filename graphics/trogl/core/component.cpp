#include "component.hpp"


#include <sstream>
#include <iomanip>
#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


size_t Component::_globID = 0;
size_t Component::_objectID = 0;
size_t Component::_shaderID = 0;
size_t Component::_materialID = 0;
size_t Component::_textureID = 0;
size_t Component::_sceneID = 0;
size_t Component::_guiID = 0;
size_t Component::_frameID = 0;


Component::Component(const Component::Type& t,
					 const std::string& name)
	: _type(t),
	  _id(++_globID),
	  _name(name)
{
	_incrementTypeId(*this);
	if (_name.empty())
		_applyNameFromType(*this);

	logDebug << (*this) << " created" << logEndl;
}


Component::Component(const Component& c)
	: _type(c._type),
	  _id(++_globID),
	  _name(c._name)
{
	_incrementTypeId(*this);
	_applyNameFromCopy(*this);

	logDebug << (*this) << " copied from " << c << logEndl;
}


Component::Component(Component&& c)
	: _type(std::move(c._type)),
	  _id(std::move(c._id)),
	  _name(std::move(c._name))
{
	logDebug << (*this) << " moved" << logEndl;
}


Component::~Component()
{
	logDebug << (*this) << " deleted" << logEndl;
}


Component& Component::operator=(const Component& c)
{
	_type = c._type;
	_id = ++_globID;
	_incrementTypeId(*this);
	_name = c._name;
	_applyNameFromCopy(*this);

	logDebug << (*this) << " copied from " << c << logEndl;
	return (*this);
}


Component& Component::operator=(Component&& c)
{
	_type = std::move(c._type);
	_id = std::move(c._id);
	_name = std::move(c._name);

	logDebug << (*this) << " moved" << logEndl;
	return (*this);
}


bool Component::operator==(const Component& c) const
{
	return (_id == c._id);
}


bool Component::operator!=(const Component& c) const
{
	return (_id != c._id);
}


bool Component::operator<(const Component& c) const
{
	return (_id < c._id);
}


bool Component::operator>(const Component& c) const
{
	return (_id > c._id);
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


Component& Component::toComponent()
{
	return (*this);
}


const Component& Component::toComponent() const
{
	return (*this);
}


void Component::setName(const std::string& name)
{
	_name = name;
}


std::string Component::toString() const
{
	return _name;
}


size_t Component::_getTypeId(const Component& c)
{
	switch (c._type)
	{
		case Type::OBJECT:
			return _objectID;
		case Type::SHADER:
			return _shaderID;
		case Type::MATERIAL:
			return _materialID;
		case Type::TEXTURE:
			return _textureID;
		case Type::SCENE:
			return _sceneID;
		case Type::GUI:
			return _guiID;
		case Type::FRAME:
			return _frameID;
	}

	return 0;
}


void Component::_incrementTypeId(const Component& c)
{
	switch (c._type)
	{
		case Type::OBJECT:
			++_objectID;
			break;
		case Type::SHADER:
			++_shaderID;
			break;
		case Type::MATERIAL:
			++_materialID;
			break;
		case Type::TEXTURE:
			++_textureID;
			break;
		case Type::SCENE:
			++_sceneID;
			break;
		case Type::GUI:
			++_guiID;
			break;
		case Type::FRAME:
			++_frameID;
			break;
	}
}


std::ostream& operator<<(std::ostream& out, const Component& c)
{
	out << "<Component"
		<< c._id << " '"
		<< c._name << "'>";

	return out;
}


void Component::_applyNameFromType(Component& c)
{
	size_t id;
	std::stringstream ss;
	switch (c._type)
	{
		case Type::OBJECT:
			id = _objectID;
			ss << "Object";
			break;
		case Type::SHADER:
			id = _shaderID;
			ss << "Shader";
			break;
		case Type::MATERIAL:
			id = _materialID;
			ss << "Material";
			break;
		case Type::TEXTURE:
			id = _textureID;
			ss << "Texture";
			break;
		case Type::SCENE:
			id = _sceneID;
			ss << "Scene";
			break;
		case Type::GUI:
			id = _guiID;
			ss << "GUI";
			break;
		case Type::FRAME:
			id = _frameID;
			ss << "Frame";
			break;
	}

	ss << std::setw(3) << std::setfill('0') << id;

	c._name = ss.str();
}


void Component::_applyNameFromCopy(Component& c)
{
	c._name.append(".copy");
}


size_t Component::Hash::operator()(const Component& c) const
{
	return c.getId();
}
