#include "diffusematerial.hpp"


#include <logger.hpp>
#include "shaders/diffuseshader.hpp"


logger_t lModule = loggerModule(Logger::Level::DEBUG, loggerDescriptionFull);


DiffuseMaterial::DiffuseMaterial(const Color& color)
	: Material("Diffusematerial", color, new DiffuseShader()),
	  _diffuse(1.0),
	  _specular(0.5)
{
	logDebug << getName() << " created." << logEndl;
}


DiffuseMaterial::~DiffuseMaterial()
{
}


const float& DiffuseMaterial::getDiffuse() const
{
	return _diffuse;
}


const float& DiffuseMaterial::getSpecular() const
{
	return _specular;
}


void DiffuseMaterial::setDiffuse(const float& diffuse)
{
	_diffuse = diffuse;
}


void DiffuseMaterial::setSpecular(const float& specular)
{
	_specular = specular;
}


void DiffuseMaterial::passToShader() const
{
//	logDebug << "Passing " << getName() << " parameters to "
//			 << _shader->getName()
//			 << logEndl;

	_shader->passAttribute("material.color", _color);
	_shader->passAttribute("material.diffuse", _diffuse);
	_shader->passAttribute("material.specular", _specular);
}
