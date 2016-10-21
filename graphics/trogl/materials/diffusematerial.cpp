#include "diffusematerial.hpp"


#include "shader.hpp"


DiffuseMaterial::DiffuseMaterial()
	: Material("Diffusematerial", DEFAULT_SHADER)
{
	// TODO: add light behavior.
}


DiffuseMaterial::~DiffuseMaterial()
{
}
