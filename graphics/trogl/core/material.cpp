#include "material.hpp"


#include <logger.hpp>


loggerModules lModules = loggerForModule(Logger::Level::DEBUG, Logger::Description::FULL);


const Color Material::DEFAULT_COLOR = Color(210, 210, 210);
const ShaderPtr Material::DEFAULT_SHADER = Shader::createPtrFromSrc("diffuse");


Material::Material(const std::string& name,
				   const Color& color,
				   const ShaderPtr& shader)
	: Component(Component::Type::MATERIAL, name),
	  _color(color),
	  _shader(shader)
{
	logModule << "Material: " << name << " with "
			  << shader->getName() << " created"
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
