#include "diffusematerial.hpp"


#include <logger.hpp>
#include "shaders/diffuseshader.hpp"


logger_t lModule = loggerModule(Logger::Level::DEBUG, loggerDescriptionFull);


DiffuseMaterial::DiffuseMaterial(const Color& color)
	: Material("Diffusematerial", color, new DiffuseShader()),
	  _diffuse(1.0),
	  _specular(0.5),
	  _hardness(7.0)
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


const float&DiffuseMaterial::getHardness() const
{
	return _hardness;
}


void DiffuseMaterial::setDiffuse(const float& diffuse)
{
	_diffuse = diffuse;
}


void DiffuseMaterial::setSpecular(const float& specular)
{
	_specular = specular;
}


void DiffuseMaterial::setHardness(const float& hardness)
{
	_hardness = hardness;
}


void DiffuseMaterial::passToShader() const
{
//	logDebug << "Passing " << getName() << " parameters to "
//			 << _shader->getName()
//			 << logEndl;

	_shader->passAttribute("material.color", _color);
	_shader->passAttribute("material.diffuse", _diffuse);
	_shader->passAttribute("material.specular", _specular);
	_shader->passAttribute("material.hardness", _hardness);
}
