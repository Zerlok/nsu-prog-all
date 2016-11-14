#include "screwshader.hpp"


#include <logger.hpp>
#include "common/utils.hpp"


const std::string ScrewShader::VS_FILE = path::join(Shader::SRC_DIR, "screw.vs");


ScrewShader::ScrewShader()
		: Shader("Screw Shader", VS_FILE, DEFAULT_FS_FILE)
{
}


ScrewShader::~ScrewShader()
{
}


void ScrewShader::registerInternalAttributes()
{
	_attrAlpha = glGetUniformLocation(_glShaderProgram, "alpha");
}


void ScrewShader::passInternalAttributes()
{
	glUniform1f(_attrAlpha, std::cos(getTimeDouble() / 10.0) * 1.21);
}


void ScrewShader::passObject(Object const*)
{
}



