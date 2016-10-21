#include "screwshader.hpp"


#include <logger.hpp>
#include "common/utils.h"


const std::string ScrewShader::SRC = "\
#version 120\n\
attribute vec4 position;\
attribute vec4 color;\
uniform float alpha;\
\
mat3 rotationMatrix(vec3 axis, float angle)\
{\
 axis = normalize(axis);\
 float s = sin(angle);\
 float c = cos(angle);\
 float nc = 1.0 - c;\
 \
 return mat3(nc * axis.x * axis.x + c,           nc * axis.x * axis.y - axis.z * s,  nc * axis.z * axis.x + axis.y * s,\
			 nc * axis.x * axis.y + axis.z * s,  nc * axis.y * axis.y + c,           nc * axis.y * axis.z - axis.x * s,\
			 nc * axis.z * axis.x - axis.y * s,  nc * axis.y * axis.z + axis.x * s,  nc * axis.z * axis.z + c);\
}\
\
int sign(vec3 v)\
{\
 if (v.y > 0.0)\
  return 1;\
 else\
  return -1;\
}\
\
void main() {\
 vec3 pos = position.xyz;\
 \
 pos = pos * rotationMatrix(vec3(0.0, 1.0, 0.0), alpha * sin(pos.y));\
 gl_Position = gl_ModelViewProjectionMatrix * vec4(pos, 1.0);\
 gl_FrontColor = color;\
}\
";


ScrewShader::ScrewShader()
		: Shader("Screw Shader", SRC)
{
}


ScrewShader::~ScrewShader()
{
}


void ScrewShader::initCustomVarsLocations(const GLuint& glShaderProgram)
{
	_attrAlpha = glGetUniformLocation(glShaderProgram, "alpha");
}


void ScrewShader::prepareForRender()
{
	glUniform1f(_attrAlpha, std::cos(getTimeDouble() / 10.0) * 1.21);
}
