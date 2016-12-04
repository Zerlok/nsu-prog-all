#include "material.hpp"


#include <logger.hpp>
#include "shaders/diffuseshader.hpp"


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


Material::Material(const std::string& name,
				   const Color& color,
				   const ShaderPtr& shader)
	: Component(Component::Type::MATERIAL, name),
	  _color(color),
	  _shader(shader)
{
	logDebug << "Material: " << getName() << " with "
			  << ((!_shader.is_null()) ? _shader->getName() : "null shader") << " created"
			  << logEndl;
}


Material::Material(const Material& mat)
	: Component(mat),
	  _color(mat._color),
	  _shader(mat._shader)
{
}


Material::Material(Material&& mat)
	: Component(mat),
	  _color(std::move(mat._color)),
	  _shader(std::move(mat._shader))
{
}


Material::~Material()
{
}


Material& Material::operator=(const Material& mat)
{
	Component::operator=(mat);
	_color = mat._color;
	_shader = mat._shader;

	return (*this);
}


Material& Material::operator=(Material&& mat)
{
	Component::operator=(mat);
	_color = std::move(mat._color);
	_shader = std::move(mat._shader);

	return (*this);
}


const Color& Material::getColor() const
{
	return _color;
}


const ShaderPtr& Material::getShader() const
{
	return _shader;
}


void Material::setColor(const Color& color)
{
	_color = color;
}


void Material::setShader(const ShaderPtr& shader)
{
	_shader = shader;
}
