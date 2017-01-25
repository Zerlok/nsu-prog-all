#include "light.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


static const vec3 defaultLampPosition {0.0, 30.0, 0.0};


Light Light::createPoint()
{
	Light lamp(Light::Type::POINT, "Point");
	lamp.setPower(1000.0);
	lamp.setPosition(defaultLampPosition);

	return std::move(lamp);
}


Light Light::createSun()
{
	Light lamp(Light::Type::SUN, "Sun");
	lamp.setPower(1.0);
	lamp.setPosition({0.0f, 10.0f, 0.0f});
	lamp.setDirection(-space::xyz::y);
	lamp.setPosition(defaultLampPosition);

	return std::move(lamp);
}


Light Light::createSpot()
{
	Light lamp(Light::Type::SPOT, "Spot");
	lamp.setPower(1000.0);
	lamp.setDirection({0.0, -1.0, 0.0});
	lamp.setInnerAngle(M_PI_2 / 9.0);
	lamp.setOutterAngle(M_PI_2 / 6.0);
	lamp.setPosition(defaultLampPosition);

	return std::move(lamp);
}


Light::Light(const Type& type, const std::string& name)
	: Object("LIGHT", name),
	  _lightType(type),
	  _power(1.0),
	  _direction(-space::xyz::y),
	  _color(Color::white),
	  _innerAngle(0.0),
	  _outterAngle(0.0)
{
	_regProperties();
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
	_regProperties();
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
	_regProperties();
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


const vec3& Light::getDirection() const
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


const glm::mat4x4& Light::getViewMatrix() const
{
	return _viewMat;
}


const glm::mat4x4& Light::getProjMatrix() const
{
	return _projMat;
}


ShaderPtr& Light::getShader()
{
	return _shader;
}


const ShaderPtr& Light::getShader() const
{
	return _shader;
}


void Light::setPower(const float& power)
{
    _power = power;
}


void Light::setDirection(const vec3& direction)
{
	if (_hasDirection(_lightType))
	{
		_direction = glm::normalize(direction);
		applyPosition();
	}
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


void Light::setShader(const ShaderPtr& sh)
{
	_shader = sh;
}


void Light::faceDirectionTo(const vec3& position)
{
	setDirection(position - _position);
}


void Light::setPosition(const vec3& position)
{
	Object::setPosition(position);
	applyPosition();
}


void Light::applyPosition()
{
	_viewMat = glm::lookAt(_position, _position + _direction, space::xyz::y);
	_projMat = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 100.0f);
}


void Light::applyRotation()
{
}


void Light::applyScale()
{
}


void Light::_regProperties()
{
	Object::_regProperties();
	_regProperty(_power);
	_regProperty(_direction);
	_regProperty(_color);
	_regProperty(_innerAngle);
	_regProperty(_outterAngle);

	_regProperty(_viewMat);
	_regProperty(_projMat);
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


std::ostream& operator<<(std::ostream& out, const Light::Type& type)
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
