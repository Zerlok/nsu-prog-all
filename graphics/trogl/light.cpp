#include "light.hpp"


#include <logger.hpp>


loggerModules lModules = loggerForModule(Logger::Level::DEBUG, Logger::Description::FULL);


Light::Light(const Type& type,
			 const ShaderPtr& shader)
	: Object(Object::Type::LIGHT),
	  _lightType(type),
	  _shader(shader)
{	
}


Light::Light(const Light& light)
	: Object(light),
	  _lightType(light._lightType),
	  _shader(light._shader)
{
}


Light::Light(Light&& light)
	: Object(light),
	  _lightType(std::move(light._lightType)),
	  _shader(std::move(light._shader))
{
}


Light::~Light()
{
}


Light& Light::operator=(const Light& light)
{
	Object::operator=(light);
	_lightType = light._lightType;
	_shader = light._shader;

	return (*this);
}


Light& Light::operator=(Light&& light)
{
	Object::operator=(light);
	_lightType = std::move(light._lightType);
	_shader = std::move(light._shader);

	return (*this);
}


const Light::Type& Light::getLightType() const
{
	return _lightType;
}


const ShaderPtr& Light::getShader() const
{
    return _shader;
}


void Light::setShader(const ShaderPtr& shader)
{
    _shader = shader;
}
