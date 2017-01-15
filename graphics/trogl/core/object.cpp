#include "object.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


const std::string Object::DEFAULT_NAME("Object");
const vec3 Object::DEFAULT_POSITION(space::xyz::zero);
const vec3 Object::DEFAULT_ROTATION(space::xyz::zero);
const vec3 Object::DEFAULT_SCALE(space::xyz::identic);


Object::Object(const Component::Type& type,
			   const std::string& name)
	: Animatable(type, name),
	  _position(DEFAULT_POSITION),
	  _rotation(DEFAULT_ROTATION),
	  _scale(DEFAULT_SCALE)
{
	_regProperties();
	logDebug << (*this) << " created." << logEndl;
}


Object::Object(const Object& obj)
	: Animatable(obj),
	  _position(obj._position),
	  _rotation(obj._rotation),
	  _scale(obj._scale)
{
	_regProperties();
	logDebug << (*this) << " copyed from " << obj << logEndl;
}


Object::Object(Object&& obj)
	: Animatable(std::move(obj)),
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
	if (!sameType(obj))
		return (*this);

	_position = obj._position;
	_rotation = obj._rotation;
	_scale = obj._scale;

	logDebug << (*this) << " copyed from " << obj << logEndl;
	return (*this);
}


Object& Object::operator=(Object&& obj)
{
	if (!sameType(obj))
		return (*this);

	_position = std::move(obj._position);
	_rotation = std::move(obj._rotation);
	_scale = std::move(obj._scale);

	logDebug << (*this) << " moved." << logEndl;
	return (*this);
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
	out << "<Object " << obj.getName()
		<< " {pos: " << obj._position
		<< " rot: " << obj._rotation
		<< " sca: " << obj._scale
		<< "}>";

	return out;
}
