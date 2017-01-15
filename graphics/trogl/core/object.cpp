#include "object.hpp"

#include <sstream>
#include <iomanip>
#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


size_t Object::_meshID = 0;
size_t Object::_lightID = 0;
size_t Object::_cameraID = 0;

const std::string Object::DEFAULT_NAME("Object");
const vec3 Object::DEFAULT_POSITION(0.0, 0.0, 0.0);
const vec3 Object::DEFAULT_ROTATION(0.0, 0.0, 0.0);
const vec3 Object::DEFAULT_SCALE(1.0, 1.0, 1.0);


Object::Object(const Type& type,
			   const std::string& name)
	: Component(Component::Type::OBJECT, name),
	  _objectType(type),
	  _position(DEFAULT_POSITION),
	  _rotation(DEFAULT_ROTATION),
	  _scale(DEFAULT_SCALE)
{
	_regProperties();
//	if (name.empty())
//		setName(_generateNameFromObjType(_objectType));

	logDebug << (*this) << " created." << logEndl;
}


Object::Object(const Object& obj)
	: Component(obj),
	  _objectType(obj._objectType),
	  _position(obj._position),
	  _rotation(obj._rotation),
	  _scale(obj._scale)
{
	_regProperties();
	logDebug << (*this) << " copyed from " << obj << logEndl;
}


Object::Object(Object&& obj)
	: Component(std::move(obj)),
	  _objectType(std::move(obj._objectType)),
	  _position(std::move(obj._position)),
	  _rotation(std::move(obj._rotation)),
	  _scale(std::move(obj._scale))
{
	_regProperties();
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


/*
Object& Object::operator+=(const Object& obj)
{
	Component::operator+=(obj);
	_position += obj._position;
	_rotation += obj._rotation;
	_scale += obj._scale;

	return (*this);
}


Object& Object::operator*=(const float& ratio)
{
	Component::operator*=(ratio);
	_position *= ratio;
	_rotation *= ratio;
	_scale *= ratio;

	return (*this);
}


Object Object::operator+(const Object& obj) const
{
	Object tmp(*this);
	tmp += obj;

	return std::move(tmp);
}


Object Object::operator*(const float& ratio) const
{
	Object tmp(*this);
	tmp *= ratio;

	return std::move(tmp);
}
*/


const Object::Type& Object::getObjectType() const
{
	return _objectType;
}


const vec3& Object::getPosition() const
{
	return _position;
}


const vec3& Object::getRotation() const
{
	return _rotation;
}


const vec3& Object::getScale() const
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


void Object::setPosition(const float& x, const float& y, const float& z)
{
	setPosition(vec3(x, y, z));
}


void Object::setRotation(const float& x, const float& y, const float& z)
{
	setRotation(vec3(x, y, z));
}


void Object::setScale(const float& x, const float& y, const float& z)
{
	setScale(vec3(x, y, z));
}


void Object::setPosition(const vec3& position)
{
	_position = position;
}


void Object::setRotation(const vec3& rotation)
{
	_rotation = rotation;
}


void Object::setScale(const vec3& scale)
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


void Object::_regProperties()
{
	_regProperty(_position);
	_regProperty(_rotation);
	_regProperty(_scale);
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

	out << " " << obj.getName()
		<< " {"
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


std::ostream&operator<<(std::ostream& out, const vec2& v)
{
	static const int precPoint = 3;
	out << "vec2("
		<< std::setprecision(precPoint) << v.x << ", "
		<< std::setprecision(precPoint) << v.y << ')';
	return out;
}


std::ostream&operator<<(std::ostream& out, const vec3& v)
{
	static const int precPoint = 3;
	out << "vec3("
		<< std::setprecision(precPoint) << v.x << ", "
		<< std::setprecision(precPoint) << v.y << ", "
		<< std::setprecision(precPoint) << v.z << ')';
	return out;
}
