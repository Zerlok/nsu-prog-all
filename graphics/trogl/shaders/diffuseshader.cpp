#include "diffuseshader.hpp"


#include <logger.hpp>
#include "common/utils.hpp"


logger_t moduleLogger = loggerModule(loggerLDebug, loggerDFull);


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
	: Shader("Diffuse Shader", {VS_FILE(), FS_FILE()})
{
	logDebug << getName() << " created." << logEndl;
}


DiffuseShader::~DiffuseShader()
{
	logDebug << getName() << " removed." << logEndl;
}


void DiffuseShader::passObject(const Object* obj) const
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


void DiffuseShader::passCamera(const Camera* camera) const


{
	const glm::vec3& pos = camera->getPosition();
	const glm::vec3& dir = camera->getLookingAtPosition();

	_externalAttributes.pass("camera.position", pos.x, pos.y, pos.z, 1.0f);
	_externalAttributes.pass("camera.direction", dir.x, dir.y, dir.z, 0.0f);
}


void DiffuseShader::passLight(const Light* light) const
{
	const glm::vec3& pos = light->getPosition();
	const glm::vec3& dir = light->getDirection();

	_externalAttributes.pass("lamp.type", int(light->getLightType()));
	_externalAttributes.pass("lamp.power", light->getPower());
	_externalAttributes.pass("lamp.color", light->getColor());
	_externalAttributes.pass("lamp.position", pos.x, pos.y, pos.z, 1.0f);
	_externalAttributes.pass("lamp.direction", dir.x, dir.y, dir.z, 0.0f);
	_externalAttributes.pass("lamp.ia", light->getInnerAngle());
	_externalAttributes.pass("lamp.oa", light->getOutterAngle());
}


void DiffuseShader::passMesh(const Mesh* mesh) const
{
	const glm::vec3& pos = mesh->getPosition();

	_externalAttributes.pass("meshPosition", pos.x, pos.y, pos.z, 1.0f);
}


void DiffuseShader::passComponent(const Component* comp) const
{
	switch (comp->getType())
	{
		case Component::Type::OBJECT:
			passObject((Object*)comp);
			break;
		default:
			break;
	}
}


void DiffuseShader::passTextures(const Textures& textures) const
{
	size_t idx = 0;
	for (const TexturePtr& texture : textures)
	{
		_externalAttributes.passEl("textures[].data", idx, texture->getSamplerId());
		_externalAttributes.passEl("textures[].offset", idx, texture->getUVOffset());
		_externalAttributes.passEl("textures[].scale", idx, texture->getUVScale());

		++idx;
	}
}


void DiffuseShader::_registerAttributes()
{
	// External.
	_externalAttributes.registerate("camera.position");
	_externalAttributes.registerate("camera.direction");

	_externalAttributes.registerate("lamp.type");
	_externalAttributes.registerate("lamp.power");
	_externalAttributes.registerate("lamp.color");
	_externalAttributes.registerate("lamp.position");
	_externalAttributes.registerate("lamp.direction");
	_externalAttributes.registerate("lamp.ia");
	_externalAttributes.registerate("lamp.oa");

	_externalAttributes.registerateArray("textures[].data", 5);
	_externalAttributes.registerateArray("textures[].offset", 5);
	_externalAttributes.registerateArray("textures[].scale", 5);

	_externalAttributes.registerate("meshPosition");

	_externalAttributes.registerate("material.color");
	_externalAttributes.registerate("material.diffuse");
	_externalAttributes.registerate("material.specular");
	_externalAttributes.registerate("material.hardness");
	_externalAttributes.registerate("texturesMixing");

	logDebug << getName() << " external attributes registered." << logEndl;
}


void DiffuseShader::_passInternalAttributes()
{
}
