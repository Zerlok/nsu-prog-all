#include "light.hpp"


#include <logger.hpp>


logger_t loggerModules = loggerModule(Logger::Level::WARNING, loggerDescriptionFull);


Light::Light(const Type& type)
	: Object(Object::Type::LIGHT),
	  _lightType(type),
	  _power(1.0),
	  _direction(0.0, 0.0, 0.0),
	  _color(Color::white),
	  _innerAngle(0.0),
	  _outterAngle(0.0)
{
	logDebug << "Light [" << _lightType << "] created." << logEndl;
}


Light::Light(const Light& light)
	: Object(light),
	  _lightType(light._lightType),
	  _power(light._power),
	  _direction(light._direction),
	  _color(light._color),
	  _innerAngle(light._innerAngle),
	  _outterAngle(light._outterAngle)
{
	logDebug << "Light [" << _lightType << "] copied." << logEndl;
}


Light::Light(Light&& light)
	: Object(light),
	  _lightType(std::move(light._lightType)),
	  _power(std::move(light._power)),
	  _direction(std::move(light._direction)),
	  _color(std::move(light._color)),
	  _innerAngle(std::move(light._innerAngle)),
	  _outterAngle(std::move(light._outterAngle))
{
	logDebug << "Light [" << _lightType << "] moved." << logEndl;
}


Light::~Light()
{
	logDebug << "Light [" << _lightType << "] deleted." << logEndl;
}


Light& Light::operator=(const Light& light)
{
	Object::operator=(light);
	_lightType = light._lightType;
	_power = light._power;
	_direction = light._direction;
	_color = light._color;
	_innerAngle = light._innerAngle;
	_outterAngle = light._outterAngle;

	return (*this);
}


Light& Light::operator=(Light&& light)
{
	Object::operator=(light);
	_lightType = std::move(light._lightType);
	_power = std::move(light._power);
	_direction = std::move(light._direction);
	_color = std::move(light._color);
	_innerAngle = std::move(light._innerAngle);
	_outterAngle = std::move(light._outterAngle);

	return (*this);
}


const Light::Type& Light::getLightType() const
{
	return _lightType;
}


const float& Light::getPower() const
{
    return _power;
}


const glm::vec3& Light::getDirection() const
{
	return _direction;
}


const Color& Light::getColor() const
{
	return _color;
}


const float& Light::getInnerAngle() const
{
	return _innerAngle;
}


const float& Light::getOutterAngle() const
{
	return _outterAngle;
}


void Light::setPower(const float& power)
{
    _power = power;
}


void Light::setDirection(const glm::vec3& direction)
{
	if (_hasDirection(_lightType))
		_direction = direction;
}


void Light::setColor(const Color& color)
{
	_color = color;
}


void Light::setInnerAngle(const float& innerAngle)
{
	if (_hasAngles(_lightType))
		_innerAngle = innerAngle;
}


void Light::setOutterAngle(const float& outterAngle)
{
	if (_hasAngles(_lightType))
		_outterAngle = outterAngle;
}


void Light::applyPosition()
{
}


void Light::applyRotation()
{
}


void Light::applyScale()
{
}


bool Light::_hasDirection(const Light::Type& type)
{
	switch (type)
	{
		case Type::SPOT:
		case Type::SUN:
			return true;

		case Type::POINT:
		case Type::AMBIENT:
			return false;
	}

	return false;
}


bool Light::_hasAngles(const Light::Type& type)
{
	switch (type)
	{
		case Type::SPOT:
			return true;

		case Type::POINT:
		case Type::SUN:
		case Type::AMBIENT:
			return false;
	}

	return false;
}


std::ostream&operator<<(std::ostream& out, const Light::Type& type)
{
	switch (type)
	{
		case Light::Type::POINT:
			out << "POINT";
			break;

		case Light::Type::SPOT:
			out << "SPOT";
			break;

		case Light::Type::SUN:
			out << "SUN";
			break;

		case Light::Type::AMBIENT:
			out << "AMBIENT";
			break;
	}

	return out;
}
