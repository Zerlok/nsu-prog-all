#include "object.hpp"

#include <logger.hpp>
#include <sstream>
#include <iomanip>


const std::string Object::DEFAULT_NAME = std::string();
size_t Object::objID = 0;


std::string Object::generateNameFromObjType(const Type& type, const size_t& id)
{
	std::stringstream ss;
	switch (type)
	{
		case Type::MESH:
			ss << "Mesh";
			break;
		case Type::LAMP:
			ss << "Lamp";
			break;
		case Type::CAMERA:
			ss << "Camera";
			break;
		default:
			break;
	}

	ss << std::setw(3) << std::setfill('0') << id;

	return ss.str();
}


Object::Object(const Type& type,
			   const std::string& name,
			   const glm::vec3& pos)
	: Component(Component::Type::OBJECT, name),
	  _object_type(type),
	  _position(pos)
{
	++objID;
	if (name.empty())
		_name = generateNameFromObjType(_object_type, objID);

	logDebug << "Object " << objID << " " << _name << " created" << logEnd;
}


Object::Object(const Object& obj)
	: Component(obj),
	  _object_type(obj._object_type),
	  _position(obj._position)
{
	logDebug << "Object " << _name << " copyed" << logEnd;
}


Object::Object(Object&& obj)
	: Component(std::move(obj)),
	  _object_type(std::move(obj._object_type)),
	  _position(std::move(obj._position))
{
}


Object::~Object()
{
	logDebug << "Object " << _name << " deleted" << logEnd;
}


Object& Object::operator=(const Object& obj)
{
	_object_type = obj._object_type;
	_name = obj._name;
	_position = obj._position;
	_rotation = obj._rotation;
	_scale = obj._scale;

	return (*this);
}


Object& Object::operator=(Object&& obj)
{
	_object_type = std::move(obj._object_type);
	_name = std::move(obj._name);
	_position = std::move(obj._position);
	_rotation = std::move(obj._rotation);
	_scale = std::move(obj._scale);

	return (*this);
}


const Object::Type& Object::getObjectType() const
{
	return _object_type;
}


const glm::vec3&Object::getPosition() const
{
	return _position;
}


void Object::setPosition(const glm::vec3& position)
{
	_position = position;
}


const glm::vec3& Object::getRotation() const
{
	return _rotation;
}


void Object::setRotation(const glm::vec3& rotation)
{
	_rotation = rotation;
}


const glm::vec3& Object::getScale() const
{
	return _scale;
}


void Object::setScale(const glm::vec3& scale)
{
	_scale = scale;
}
