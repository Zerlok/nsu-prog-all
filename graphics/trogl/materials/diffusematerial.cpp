#include "diffusematerial.hpp"


#include <logger.hpp>
#include "shaders/diffuseshader.hpp"


logger_t lModule = loggerModule(Logger::Level::WARNING, loggerDescriptionFull);


DiffuseMaterial::DiffuseMaterial(const Color& color)
	: Material("Diffusematerial", color, new DiffuseShader())
{
	logDebug << "Created material" << logEndl;
}


DiffuseMaterial::~DiffuseMaterial()
{
}
