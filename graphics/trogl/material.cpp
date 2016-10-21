#include "material.hpp"


const ShaderPtr Material::DEFAULT_SHADER = new Shader("Diffuse vertex shader");


Material::Material(const std::string& name,
				   const ShaderPtr& shader)
	: Component(Component::Type::MATERIAL, name),
	  _shader(shader)
{
}


Material::Material(const Material& mat)
	: Component(mat),
	  _shader(mat._shader)
{
}


Material::Material(Material&& mat)
	: Component(mat),
	  _shader(std::move(mat._shader))
{
}


Material::~Material()
{
}


Material& Material::operator=(const Material& mat)
{
	Component::operator=(mat);
	_shader = mat._shader;

	return (*this);
}


Material& Material::operator=(Material&& mat)
{
	Component::operator=(mat);
	_shader = std::move(mat._shader);

	return (*this);
}


const ShaderPtr& Material::getShader() const
{
	return _shader;
}


void Material::setShader(const ShaderPtr& shader)
{
	_shader = shader;
}
