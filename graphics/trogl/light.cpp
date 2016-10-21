#include "light.hpp"


Light::Light(const Type& type)
	: Object(Object::Type::LIGHT),
	  _lightType(type)
{	
}


Light::Light(const Light& light)
	: Object(light),
	  _lightType(light._lightType)
{
}


Light::Light(Light&& light)
	: Object(light),
	  _lightType(std::move(light._lightType))
{
}


Light::~Light()
{
}


Light& Light::operator=(const Light& light)
{
	Object::operator=(light);
	_lightType = light._lightType;

	return (*this);
}


Light& Light::operator=(Light&& light)
{
	Object::operator=(light);
	_lightType = std::move(light._lightType);

	return (*this);
}


const Light::Type& Light::getLightType() const
{
	return _lightType;
}
