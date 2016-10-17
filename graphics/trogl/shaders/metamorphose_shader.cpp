#include "metamorphose_shader.h"


#include <logger.hpp>
#include "common/utils.h"


const std::string MetamorphoseShader::SRC = "\
#version 120\n\
attribute vec4 position;\
attribute vec4 color;\
uniform float cosSqAlpha;\
uniform vec4 constColor;\
\
void main() {\
 vec3 pos = position.xyz;\
 float k = 1 / sqrt(dot(pos, pos));\
 pos = pos * cosSqAlpha + pos * k * (1 - cosSqAlpha);\
 gl_Position = gl_ModelViewProjectionMatrix * vec4(pos, 1.0);\
 gl_FrontColor = color * constColor;\
}\
";


MetamorphoseShader::MetamorphoseShader()
	: Shader("Metamorph Shader", SRC)
{
}


MetamorphoseShader::~MetamorphoseShader()
{
}


void MetamorphoseShader::initUniformsLocations(const GLuint& glShaderProgram)
{
	_attrCosSqAlpha = glGetUniformLocation(glShaderProgram, "cosSqAlpha");
}


void MetamorphoseShader::prepareForRender()
{
	glUniform1f(_attrCosSqAlpha, std::pow(std::cos(getTime() / 10.0), 2));
}
