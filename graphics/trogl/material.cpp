#include "material.hpp"


Material::Material(const std::string& name)
	: Component(Component::Type::MATERIAL, name)
{
}


Material::~Material()
{
}
