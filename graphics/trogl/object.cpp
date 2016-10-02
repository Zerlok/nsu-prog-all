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
			   const Point& pos)
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


const Object::Type& Object::getObjectType() const
{
	return _object_type;
}


const Point&Object::getPosition() const
{
	return _position;
}


void Object::setPosition(const Point& position)
{
	_position = position;
}


const Point& Object::getRotation() const
{
	return _rotation;
}


void Object::setRotation(const Point& rotation)
{
	_rotation = rotation;
}


const Point& Object::getScale() const
{
	return _scale;
}


void Object::setScale(const Point& scale)
{
	_scale = scale;
}
