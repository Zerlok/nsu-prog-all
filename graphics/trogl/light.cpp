#include "light.hpp"


Light::Light(const Type& type)
	: Object(Object::Type::LIGHT),
	  _light_type(type)
{	
}


Light::Light(const Light& light)
	: Object(light),
	  _light_type(light._light_type)
{
}


Light::Light(Light&& light)
	: Object(light),
	  _light_type(std::move(light._light_type))
{
}


Light::~Light()
{
}


Light& Light::operator=(const Light& light)
{
	Object::operator=(light);
	_light_type = light._light_type;

	return (*this);
}


Light& Light::operator=(Light&& light)
{
	Object::operator=(light);
	_light_type = std::move(light._light_type);

	return (*this);
}


const Light::Type& Light::getLightType() const
{
    return _light_type;
}
