#include "lamp.hpp"


#include "shaders/diffuseshader.hpp"


Lamp::Lamp()
	: Light(Light::Type::POINT, new DiffuseShader())
{
}


Lamp::~Lamp()
{
}

