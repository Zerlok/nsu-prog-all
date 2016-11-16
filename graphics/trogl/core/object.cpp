#include "object.hpp"

#include <sstream>
#include <iomanip>
#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


size_t Object::_meshID = 0;
size_t Object::_lightID = 0;
size_t Object::_cameraID = 0;

const std::string Object::DEFAULT_NAME = std::string();
const Object::vec Object::DEFAULT_POSITION = Object::vec(0.0, 0.0, 0.0);
const Object::vec Object::DEFAULT_ROTATION = Object::vec(0.0, 0.0, 0.0);
const Object::vec Object::DEFAULT_SCALE = Object::vec(1.0, 1.0, 1.0);
const Object::vec Object::AXIS_X = Object::vec(1.0, 0.0, 0.0);
const Object::vec Object::AXIS_Y = Object::vec(0.0, 1.0, 0.0);
const Object::vec Object::AXIS_Z = Object::vec(0.0, 0.0, 1.0);


Object::Object(const Type& type,
			   const std::string& name)
	: Component(Component::Type::OBJECT, name),
	  _objectType(type),
	  _position(DEFAULT_POSITION),
	  _rotation(DEFAULT_ROTATION),
	  _scale(DEFAULT_SCALE)
{
	if (name.empty())
		setName(_generateNameFromObjType(_objectType));

	logDebug << (*this) << " created." << logEndl;
}


Object::Object(const Object& obj)
	: Component(obj),
	  _objectType(obj._objectType),
	  _position(obj._position),
	  _rotation(obj._rotation),
	  _scale(obj._scale)
{
	logDebug << (*this) << " copyed from " << obj << logEndl;
}


Object::Object(Object&& obj)
	: Component(std::move(obj)),
	  _objectType(std::move(obj._objectType)),
	  _position(std::move(obj._position)),
	  _rotation(std::move(obj._rotation)),
	  _scale(std::move(obj._scale))
{
	logDebug << (*this) << " moved." << logEndl;
}


Object::~Object()
{
	logDebug << (*this) << " deleted." << logEndl;
}


Object& Object::operator=(const Object& obj)
{
	Component::operator=(obj);
	_objectType = obj._objectType;
	_position = obj._position;
	_rotation = obj._rotation;
	_scale = obj._scale;

	logDebug << (*this) << " copyed from " << obj << logEndl;
	return (*this);
}


Object& Object::operator=(Object&& obj)
{
	Component::operator=(obj);
	_objectType = std::move(obj._objectType);
	_position = std::move(obj._position);
	_rotation = std::move(obj._rotation);
	_scale = std::move(obj._scale);

	logDebug << (*this) << " moved." << logEndl;
	return (*this);
}


const Object::Type& Object::getObjectType() const
{
	return _objectType;
}


const Object::vec& Object::getPosition() const
{
	return _position;
}


const Object::vec& Object::getRotation() const
{
	return _rotation;
}


const Object::vec& Object::getScale() const
{
	return _scale;
}


Object& Object::toObject()
{
	return (*this);
}


const Object& Object::toObject() const
{
	return (*this);
}


void Object::setPosition(const Object::vec& position)
{
	_position = position;
}


void Object::setRotation(const Object::vec& rotation)
{
	_rotation = rotation;
}


void Object::setScale(const Object::vec& scale)
{
	_scale = scale;
}


std::ostream& operator<<(std::ostream& out, const Object& obj)
{
	out << "<Object::";
	switch (obj._objectType)
	{
		case Object::Type::MESH:
			out << "Mesh";
			break;
		case Object::Type::LIGHT:
			out << "Light";
			break;
		case Object::Type::CAMERA:
			out << "Camera";
			break;
	}

	out << " '" << obj.getName()
		<< "' {"
		<< "pos: " << obj._position
		<< " rot: " << obj._rotation
		<< " sca: " << obj._scale
		<< "}>";

	return out;
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
	}

	ss << std::setw(3) << std::setfill('0') << id;

	return ss.str();
}


std::ostream&operator<<(std::ostream& out, const Object::vec& v)
{
	static const int precPoint = 3;
	out << "vec3("
		<< std::setprecision(precPoint) << v.x << ", "
		<< std::setprecision(precPoint) << v.y << ", "
		<< std::setprecision(precPoint) << v.z << ')';
	return out;
}
