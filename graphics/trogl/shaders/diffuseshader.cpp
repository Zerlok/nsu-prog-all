#include "diffuseshader.hpp"


#include <logger.hpp>
#include "common/utils.hpp"


logger_t loggerModules = loggerModule(Logger::Level::WARNING,
										 loggerDescriptionFull);


std::string DiffuseShader::VS_FILE()
{
	static std::string vs_file = path::join(Shader::SRC_DIR, "diffuse.vs");
	return vs_file;
}


std::string DiffuseShader::FS_FILE()
{
	static std::string fs_file = path::join(Shader::SRC_DIR, "diffuse.fs");
	return fs_file;
}


DiffuseShader::DiffuseShader()
	: Shader("Diffuse Shader", VS_FILE(), FS_FILE()),
	  _attrMeshPosition(0),
	  _attrLampType(0),
	  _attrLampPosition(0),
	  _attrLampPower(0),
	  _attrLampDirection(0),
	  _attrLampColor(0),
	  _attrLampInnerAngle(0),
	  _attrLampOutterAngle(0)
{
	logDebug << "Loading shader from files: " << VS_FILE << ' ' << FS_FILE << logEndl;
}


DiffuseShader::~DiffuseShader()
{
}


void DiffuseShader::passMesh(Mesh const* mesh)
{
	const glm::vec3& meshPos = mesh->getPosition();
	glUniform4f(_attrMeshPosition, meshPos.x, meshPos.y, meshPos.z, 1.0f);
}


void DiffuseShader::passLight(Light const* light)
{
	const glm::vec3& lightPos = light->getPosition();
	const glm::vec3& lightDir = light->getDirection();
	const Color lightColor = light->getColor();

	glUniform1i(_attrLampType, int(light->getLightType()));
	glUniform4f(_attrLampPosition, lightPos.x, lightPos.y, lightPos.z, 1.0f);
	glUniform1f(_attrLampPower, light->getPower());
	glUniform4f(_attrLampDirection, lightDir.x, lightDir.y, lightDir.z, 0.0f);
	glUniform4f(_attrLampColor, lightColor.getRedF(), lightColor.getGreenF(), lightColor.getBlueF(), 1.0f);
	glUniform1f(_attrLampInnerAngle, light->getInnerAngle());
	glUniform1f(_attrLampOutterAngle, light->getOutterAngle());
}


void DiffuseShader::initCustomVarsLocations()
{
	_attrMeshPosition = glGetUniformLocation(_glShaderProgram, "meshPosition");

	_attrLampType = glGetUniformLocation(_glShaderProgram, "lampType");
	_attrLampPosition = glGetUniformLocation(_glShaderProgram, "lampPosition");
	_attrLampPower = glGetUniformLocation(_glShaderProgram, "lampPower");
	_attrLampDirection = glGetUniformLocation(_glShaderProgram, "lampDirection");
	_attrLampColor = glGetUniformLocation(_glShaderProgram, "lampColor");
	_attrLampInnerAngle = glGetUniformLocation(_glShaderProgram, "lampIA");
	_attrLampOutterAngle = glGetUniformLocation(_glShaderProgram, "lampOA");

	logInfo << isCompiledSuccessfuly() << logEndl;
	logInfo << _attrLampType << ' '
			<< _attrLampPosition << ' '
			<< _attrLampPower << ' '
			<< _attrLampDirection << ' '
			<< _attrLampColor << ' '
			<< _attrLampInnerAngle << ' '
			<< _attrLampOutterAngle << logEndl;
}


void DiffuseShader::passObject(Object const* obj)
{
	if (obj != nullptr)
		return;

	switch (obj->getObjectType())
	{
		case Object::Type::MESH:
			passMesh((Mesh*)obj);
			break;
		case Object::Type::LIGHT:
			passLight((Light*)obj);
			break;
		default:
			break;
	}
}


void DiffuseShader::prepareForRender()
{
}