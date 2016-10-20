#include "material.hpp"


const ShaderPtr Material::DEFAULT_VERTEX_SHADER = new Shader(
		"Diffuse vertex shader",
		"#version 120\n"
		"attribute vec4 position;\n"
		"attribute vec4 color;\n"
		"uniform vec4 constColor;\n"
		"void main() {\n"
		"  gl_Position = gl_ModelViewProjectionMatrix * position;\n"
		"  gl_FrontColor = color * constColor;\n"
		"}\n"
);
const ShaderPtr Material::DEFAULT_FRAGMENT_SHADER = new Shader(
		"Diffuse fragment shader",
		"#version 120\n"
		"void main() {\n"
		"  gl_FragColor = gl_Color;\n"
		"}\n"
);


Material::Material(const std::string& name,
				   const ShaderPtr& vertexShader,
				   const ShaderPtr& fragmentShader)
	: Component(Component::Type::MATERIAL, name),
	  _vertexShader(vertexShader),
	  _fragmentShader(fragmentShader)
{
}


Material::Material(const Material& mat)
	: Component(mat),
	  _vertexShader(mat._vertexShader),
	  _fragmentShader(mat._fragmentShader)
{
}


Material::Material(Material&& mat)
	: Component(mat),
	  _vertexShader(std::move(mat._vertexShader)),
	  _fragmentShader(std::move(mat._fragmentShader))
{
}


Material::~Material()
{
}


Material& Material::operator=(const Material& mat)
{
	Component::operator=(mat);
	_vertexShader = mat._vertexShader;
	_fragmentShader = mat._fragmentShader;

	return (*this);
}


Material& Material::operator=(Material&& mat)
{
	Component::operator=(mat);
	_vertexShader = std::move(mat._vertexShader);
	_fragmentShader = std::move(mat._fragmentShader);

	return (*this);
}


const ShaderPtr& Material::getVertexShader() const
{
	return _vertexShader;
}


const ShaderPtr& Material::getFragmentShader() const
{
	return _fragmentShader;
}


void Material::setVertexShader(const ShaderPtr& vertexShader)
{
	_vertexShader = vertexShader;
}


void Material::setFragmentShader(const ShaderPtr& fragmentShader)
{
	_fragmentShader = fragmentShader;
}
