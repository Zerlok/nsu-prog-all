#include "diffusematerial.hpp"


#include <logger.hpp>
#include "shaders/diffuseshader.hpp"


logger_t lModule = loggerModule(loggerLWarning, loggerDFull);


DiffuseMaterial::DiffuseMaterial(const Color& color,
								 const float& diffuse,
								 const float& specular,
								 const float& hardness)
	: Material("Diffusematerial", color),
	  _diffuse(diffuse),
	  _specular(specular),
	  _hardness(hardness)
{
	static const ShaderPtr diffuseShader = new DiffuseShader();
	_setShader(diffuseShader);
	logDebug << getName() << " created." << logEndl;
}


DiffuseMaterial::DiffuseMaterial(const DiffuseMaterial& mat)
	: Material(mat),
	  _diffuse(mat._diffuse),
	  _specular(mat._specular),
	  _hardness(mat._hardness)
{
	logDebug << getName() << " copied from " << mat.getName() << logEndl;
}


DiffuseMaterial::DiffuseMaterial(DiffuseMaterial&& mat)
	: Material(std::move(mat)),
	  _diffuse(std::move(mat._diffuse)),
	  _specular(std::move(mat._specular)),
	  _hardness(std::move(mat._hardness))
{
	logDebug << getName() << " moved." << logEndl;
}


DiffuseMaterial::~DiffuseMaterial()
{
	logDebug << getName() << " removed." << logEndl;
}


DiffuseMaterial& DiffuseMaterial::operator=(const DiffuseMaterial& mat)
{
	Material::operator=(mat);
	_diffuse = mat._diffuse;
	_specular = mat._specular;
	_hardness = mat._hardness;

	logDebug << getName() << " copied from " << mat.getName() << logEndl;
	return (*this);
}


DiffuseMaterial& DiffuseMaterial::operator=(DiffuseMaterial&& mat)
{
	Material::operator=(std::move(mat));
	_diffuse = std::move(mat._diffuse);
	_specular = std::move(mat._specular);
	_hardness = std::move(mat._hardness);

	logDebug << getName() << " moved." << logEndl;
	return (*this);
}


/*
DiffuseMaterial& DiffuseMaterial::operator+=(const DiffuseMaterial& mat)
{
	Material::operator+=(mat);
	_diffuse += mat._diffuse;
	_specular += mat._specular;
	_hardness += mat._hardness;

	return (*this);
}


DiffuseMaterial& DiffuseMaterial::operator*=(const float& ratio)
{
	Material::operator*=(ratio);
	_diffuse *= ratio;
	_specular *= ratio;
	_hardness *= ratio;

	return (*this);
}


DiffuseMaterial DiffuseMaterial::operator+(const DiffuseMaterial& mat) const
{
	DiffuseMaterial tmp(*this);
	tmp += mat;

	return std::move(tmp);
}


DiffuseMaterial DiffuseMaterial::operator*(const float& ratio) const
{
	DiffuseMaterial tmp(*this);
	tmp *= ratio;

	return std::move(tmp);
}
*/


const float& DiffuseMaterial::getDiffuse() const
{
	return _diffuse;
}


const float& DiffuseMaterial::getSpecular() const
{
	return _specular;
}


const float& DiffuseMaterial::getHardness() const
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


void DiffuseMaterial::use()
{
	Material::use();

	_shader->passUniform("material.diffuse", _diffuse);
	_shader->passUniform("material.specular", _specular);
	_shader->passUniform("material.hardness", _hardness);
}
