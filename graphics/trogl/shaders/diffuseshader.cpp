#include "diffuseshader.hpp"


#include <logger.hpp>
#include "common/utils.h"


loggerModules lModules = loggerForModule(Logger::Level::DEBUG,
										 Logger::Description::FULL);


const std::string DiffuseShader::VS_FILE = path::join(Shader::SRC_DIR, "diffuse.vs");
const std::string DiffuseShader::FS_FILE = path::join(Shader::SRC_DIR, "diffuse.fs");


DiffuseShader::DiffuseShader()
	: Shader("Diffuse Shader", VS_FILE, FS_FILE)
{
}


DiffuseShader::~DiffuseShader()
{
}


void DiffuseShader::initCustomVarsLocations()
{
}


void DiffuseShader::prepareForRender()
{
}
