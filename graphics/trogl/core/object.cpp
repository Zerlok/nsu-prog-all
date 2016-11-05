#include "object.hpp"

#include <sstream>
#include <iomanip>
#include <logger.hpp>


logger_t loggerModules = loggerModule(Logger::Level::WARNING, loggerDescriptionFull);


size_t Object::_meshID = 0;
size_t Object::_lightID = 0;
size_t Object::_cameraID = 0;

const std::string Object::DEFAULT_NAME = std::string();
const glm::vec3 Object::DEFAULT_POSITION = glm::vec3(0.0, 0.0, 0.0);
const glm::vec3 Object::DEFAULT_ROTATION = glm::vec3(0.0, 0.0, 0.0);
const glm::vec3 Object::DEFAULT_SCALE = glm::vec3(1.0, 1.0, 1.0);
const glm::vec3 Object::AXIS_X = glm::vec3(1.0, 0.0, 0.0);
const glm::vec3 Object::AXIS_Y = glm::vec3(0.0, 1.0, 0.0);
const glm::vec3 Object::AXIS_Z = glm::vec3(0.0, 0.0, 1.0);


Object::Object(const Type& type,
			   const std::string& name)
	: Component(Component::Type::OBJECT, name),
	  _object_type(type),
	  _position(DEFAULT_POSITION),
	  _rotation(DEFAULT_ROTATION),
	  _scale(DEFAULT_SCALE)
{
	if (name.empty())
		_name = _generateNameFromObjType(_object_type);

	logDebug << "Object " << _meshID << " " << _name << " created" << logEndl;
}


Object::Object(const Object& obj)
	: Component(obj),
	  _object_type(obj._object_type),
	  _position(obj._position),
	  _rotation(obj._rotation),
	  _scale(obj._scale)
{
	logDebug << "Object " << _name << " copyed" << logEndl;
}


Object::Object(Object&& obj)
	: Component(std::move(obj)),
	  _object_type(std::move(obj._object_type)),
	  _position(std::move(obj._position)),
	  _rotation(std::move(obj._rotation)),
	  _scale(std::move(obj._scale))
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


const glm::vec3& Object::getRotation() const
{
	return _rotation;
}


const glm::vec3& Object::getScale() const
{
	return _scale;
}


void Object::setPosition(const glm::vec3& position)
{
	_position = position;
}


void Object::setRotation(const glm::vec3& rotation)
{
	_rotation = rotation;
}


void Object::setScale(const glm::vec3& scale)
{
	_scale = scale;
}


std::string Object::_generateNameFromObjType(const Type& type)
{
	size_t id;
	std::stringstream ss;
	switch (type)
	{
		case Type::MESH:
			id = ++_meshID;
			ss << "Mesh";
			break;
		case Type::LIGHT:
			id = ++_lightID;
			ss << "Light";
			break;
		case Type::CAMERA:
			id = ++_cameraID;
			ss << "Camera";
			break;
		default:
			break;
	}

	ss << std::setw(3) << std::setfill('0') << id;

	return ss.str();
}
