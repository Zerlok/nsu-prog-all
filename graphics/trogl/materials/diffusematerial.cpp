#include "diffusematerial.hpp"


#include "shader.hpp"


DiffuseMaterial::DiffuseMaterial()
	: Material("Diffusematerial", Material::DEFAULT_SHADER)
{
	// TODO: add light behavior.
}


DiffuseMaterial::~DiffuseMaterial()
{
}
