#include "diffuseshader.hpp"


#include <logger.hpp>


loggerType loggerInstance = loggerForModule(Logger::Level::INFO,
											Logger::Description::FULL);


const std::string DiffuseShader::SRC = \
"#version 120\n"
"attribute vec4 position;\n"
"attribute vec4 color;\n"
"uniform vec4 lampPosition;\n"
"void main() {\n"
"  gl_FragColor = color;\n"
"}\n";


DiffuseShader::DiffuseShader()
	: Shader("Lamp diffuse shader", Shader::DEFAULT_VERTEX_SRC, SRC)
{
}


DiffuseShader::~DiffuseShader()
{
}


void DiffuseShader::initCustomVarsLocations(const GLuint& glProgram)
{

}


void DiffuseShader::prepareForRender()
{
}

