#include "diffuseshader.hpp"


#include <logger.hpp>
#include "common/utils.hpp"


logger_t loggerModules = loggerModule(Logger::Level::DEBUG, loggerDescriptionFull);


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
	  _attrLamp()
{
}


DiffuseShader::~DiffuseShader()
{
}


void DiffuseShader::passMesh(Mesh const* mesh)
{
	const glm::vec3& meshPos = mesh->getPosition();
	glUniform4f(_attrMeshPosition, meshPos.x, meshPos.y, meshPos.z, 1.0);
}


void DiffuseShader::passLight(Light const* light)
{
	const glm::vec3& lightPos = light->getPosition();
	const glm::vec3& lightDir = light->getDirection();
	const Color lightColor = light->getColor();

	glUniform1i(_attrLamp.type, int(light->getLightType()));
	glUniform4f(_attrLamp.position, lightPos.x, lightPos.y, lightPos.z, 1.0f);
	glUniform1f(_attrLamp.power, light->getPower());
	glUniform4f(_attrLamp.direction, lightDir.x, lightDir.y, lightDir.z, 0.0f);
	glUniform4f(_attrLamp.color, lightColor.getRedF(), lightColor.getGreenF(), lightColor.getBlueF(), 1.0f);
	glUniform1f(_attrLamp.innerAngle, light->getInnerAngle());
	glUniform1f(_attrLamp.outterAngle, light->getOutterAngle());
}


void DiffuseShader::registerInternalAttributes()
{
	_attrMeshPosition = glGetUniformLocation(_glShaderProgram, "meshPosition");

	_attrLamp.type = glGetUniformLocation(_glShaderProgram, "lamp.type");
	_attrLamp.position = glGetUniformLocation(_glShaderProgram, "lamp.position");
	_attrLamp.power = glGetUniformLocation(_glShaderProgram, "lamp.power");
	_attrLamp.direction = glGetUniformLocation(_glShaderProgram, "lamp.direction");
	_attrLamp.color = glGetUniformLocation(_glShaderProgram, "lamp.color");
	_attrLamp.innerAngle = glGetUniformLocation(_glShaderProgram, "lamp.ia");
	_attrLamp.outterAngle = glGetUniformLocation(_glShaderProgram, "lamp.oa");
}


void DiffuseShader::passObject(Object const* obj)
{
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


void DiffuseShader::passInternalAttributes()
{
}
