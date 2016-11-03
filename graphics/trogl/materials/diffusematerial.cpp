#include "diffusematerial.hpp"


#include <logger.hpp>
#include "shaders/diffuseshader.hpp"


loggerModules lModule = loggerForModule(Logger::Level::WARNING, Logger::Description::FULL);


DiffuseMaterial::DiffuseMaterial(const Color& color)
	: Material("Diffusematerial", color, new DiffuseShader())
{
	logModule << "Created material" << logEndl;
}


DiffuseMaterial::~DiffuseMaterial()
{
}
