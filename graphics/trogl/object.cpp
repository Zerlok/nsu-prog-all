#include "object.hpp"

#include <logger.hpp>
#include <sstream>
#include <iomanip>


size_t Object::_objID = 0;

const std::string Object::DEFAULT_NAME = std::string();
const glm::vec3 Object::DEFAULT_POSITION = glm::vec3(0.0, 0.0, 0.0);
const glm::vec3 Object::DEFAULT_ROTATION = glm::vec3(0.0, 0.0, 0.0);
const glm::vec3 Object::DEFAULT_SCALE = glm::vec3(1.0, 1.0, 1.0);

const glm::vec3 Object::AXIS_X = glm::vec3(1.0, 0.0, 0.0);
const glm::vec3 Object::AXIS_Y = glm::vec3(0.0, 1.0, 0.0);
const glm::vec3 Object::AXIS_Z = glm::vec3(0.0, 0.0, 1.0);


Object::Object(const Type& type,
			   const std::string& name,
			   const glm::vec3& pos)
	: Component(Component::Type::OBJECT, name),
	  _object_type(type),
	  _position(pos)
{
	++_objID;
	if (name.empty())
		_name = _generateNameFromObjType(_object_type, _objID);

	logDebug << "Object " << _objID << " " << _name << " created" << logEndl;
}


Object::Object(const Object& obj)
	: Component(obj),
	  _object_type(obj._object_type),
	  _position(obj._position)
{
	logDebug << "Object " << _name << " copyed" << logEndl;
}


Object::Object(Object&& obj)
	: Component(std::move(obj)),
	  _object_type(std::move(obj._object_type)),
	  _position(std::move(obj._position))
{
}


Object::~Object()
{
	logDebug << "Object " << _name << " deleted" << logEndl;
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


void Object::applyPosition()
{
	_position = DEFAULT_POSITION;
}


void Object::applyRotation()
{
	_rotation = DEFAULT_ROTATION;
}


void Object::applyScale()
{
	_scale = DEFAULT_SCALE;
}


std::string Object::_generateNameFromObjType(const Type& type, const size_t& id)
{
	std::stringstream ss;
	switch (type)
	{
		case Type::MESH:
			ss << "Mesh";
			break;
		case Type::LIGHT:
			ss << "Light";
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
