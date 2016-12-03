#include "diffuseshader.hpp"


#include <logger.hpp>
#include "common/utils.hpp"


logger_t moduleLogger = loggerModule(Logger::Level::DEBUG, loggerDFull);


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
	: Shader("Diffuse Shader", VS_FILE(), DEFAULT_GS_FILE, FS_FILE())
{
}


DiffuseShader::~DiffuseShader()
{
}


void DiffuseShader::passMesh(Mesh const* mesh)
{
	const glm::vec3& pos = mesh->getPosition();

	_externalAttributes.pass("meshPosition", pos.x, pos.y, pos.z, 1.0f);
}


void DiffuseShader::passLight(Light const* light)
{
	const glm::vec3& pos = light->getPosition();
	const glm::vec3& dir = light->getDirection();

	_internalAttributes.pass("lamp.type", int(light->getLightType()));
	_internalAttributes.pass("lamp.power", light->getPower());
	_internalAttributes.pass("lamp.color", light->getColor());
	_internalAttributes.pass("lamp.position", pos.x, pos.y, pos.z, 1.0f);
	_internalAttributes.pass("lamp.direction", dir.x, dir.y, dir.z, 0.0f);
	_internalAttributes.pass("lamp.ia", light->getInnerAngle());
	_internalAttributes.pass("lamp.oa", light->getOutterAngle());
}


void DiffuseShader::passCamera(const Camera* camera)
{
	const glm::vec3& pos = camera->getPosition();
	const glm::vec3& dir = camera->getLookingAtPosition();

	_internalAttributes.pass("camera.position", pos.x, pos.y, pos.z, 1.0f);
	_internalAttributes.pass("camera.direction", dir.x, dir.y, dir.z, 0.0f);
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
		case Object::Type::CAMERA:
			passCamera((Camera*)obj);
		default:
			break;
	}
}


void DiffuseShader::_registerAttributes()
{
	// Internal.
	_internalAttributes.registerate("camera.position");
	_internalAttributes.registerate("camera.direction");

	_internalAttributes.registerate("lamp.type");
	_internalAttributes.registerate("lamp.power");
	_internalAttributes.registerate("lamp.color");
	_internalAttributes.registerate("lamp.position");
	_internalAttributes.registerate("lamp.direction");
	_internalAttributes.registerate("lamp.ia");
	_internalAttributes.registerate("lamp.oa");

	// External.
	_externalAttributes.registerate("meshPosition");
	_externalAttributes.registerate("material.color");
	_externalAttributes.registerate("material.diffuse");
	_externalAttributes.registerate("material.specular");
	_externalAttributes.registerate("material.hardness");
}


void DiffuseShader::_passInternalAttributes()
{
}
