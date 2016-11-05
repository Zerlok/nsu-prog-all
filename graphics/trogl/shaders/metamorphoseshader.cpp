#include "metamorphoseshader.hpp"


#include <logger.hpp>
#include "common/utils.hpp"


logger_t loggerModules = loggerModule(Logger::Level::WARNING,
										 loggerDescriptionFull);


const std::string MetamorphoseShader::VS_FILE = path::join(Shader::SRC_DIR, "metamorph.vs");


MetamorphoseShader::MetamorphoseShader()
	: Shader("Metamorph Shader", VS_FILE, DEFAULT_FS_FILE)
{
	logDebug << "Metamorph Shader created" << std::endl;
}


MetamorphoseShader::~MetamorphoseShader()
{
}


void MetamorphoseShader::initCustomVarsLocations()
{
	_attrCosSqAlpha = glGetUniformLocation(_glShaderProgram, "cosSqAlpha");
}


void MetamorphoseShader::prepareForRender()
{
	glUniform1f(_attrCosSqAlpha, std::pow(std::cos(getTimeDouble() / 10.0), 2));
}


void MetamorphoseShader::passObject(Object const*)
{
}
