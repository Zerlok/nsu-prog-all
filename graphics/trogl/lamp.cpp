#include "lamp.hpp"


Lamp::Lamp()
	: Object(Object::Type::LAMP)
{	
}


Lamp::Lamp(const Lamp& lamp)
	: Object(lamp)
{
}


Lamp::Lamp(Lamp&& lamp)
	: Object(lamp)
{
}


Lamp::~Lamp()
{
}


Lamp& Lamp::operator=(const Lamp& lamp)
{
	Object::operator=(lamp);

	return (*this);
}


Lamp& Lamp::operator=(Lamp&& lamp)
{
	Object::operator=(lamp);

	return (*this);
}
