#include "shader.hpp"


Shader::Shader(const std::string& name, const std::string& src)
	: Component(Component::Type::SHADER, name),
	  _src(src)
{
}


Shader::Shader(const Shader& sh)
	: Component(sh),
	  _src(sh._src)
{
}


Shader::Shader(Shader&& sh)
	: Component(sh),
	  _src(std::move(sh._src))
{
}


Shader::~Shader()
{
}


Shader& Shader::operator=(const Shader& sh)
{
	Component::operator=(sh);
	_src = sh._src;

	return (*this);
}


Shader& Shader::operator=(Shader&& sh)
{
	Component::operator=(sh);
	_src = std::move(sh._src);

	return (*this);
}


void Shader::initUniformsLocations(const GLuint&)
{
}


void Shader::prepareForRender()
{
}


const char* Shader::getSrcPtr() const
{
	return _src.data();
}


const std::string& Shader::getSrc() const
{
	return _src;
}
