#include "shader.hpp"


Shader::Shader(const std::string& src)
	: _src(src)
{
}


Shader::Shader(const Shader& sh)
	: _src(sh._src)
{
}


Shader::~Shader()
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
