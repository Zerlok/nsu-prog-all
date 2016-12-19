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
	: Shader("Diffuse Shader", {VS_FILE(), FS_FILE()})
{
}


DiffuseShader::~DiffuseShader()
{
}


void DiffuseShader::passTexture(const Texture* texture)
{
	_externalAttributes.pass("text.data", texture->getSamplerId());
	_externalAttributes.pass("text.offset", texture->getUVOffset());
	_externalAttributes.pass("text.scale", texture->getUVScale());
	_externalAttributes.pass("text.colorMix", texture->getColorMix());
	_externalAttributes.pass("text.binded", 1.0f);
}


void DiffuseShader::passMesh(const Mesh* mesh)
{
	const glm::vec3& pos = mesh->getPosition();

	_externalAttributes.pass("meshPosition", pos.x, pos.y, pos.z, 1.0f);
}


void DiffuseShader::passLight(const Light* light)
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


void DiffuseShader::passCamera(const Camera* camera)
{
	const glm::vec3& pos = camera->getPosition();
	const glm::vec3& dir = camera->getLookingAtPosition();

	_externalAttributes.pass("camera.position", pos.x, pos.y, pos.z, 1.0f);
	_externalAttributes.pass("camera.direction", dir.x, dir.y, dir.z, 0.0f);
}


void DiffuseShader::passComponent(const Component* comp)
{
	switch (comp->getType())
	{
		case Component::Type::OBJECT:
			passObject((Object*)comp);
			break;
		case Component::Type::TEXTURE:
			passTexture((Texture*)comp);
			break;
		default:
			break;
	}
}


void DiffuseShader::passObject(const Object* obj)
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

	_externalAttributes.registerate("text.data");
	_externalAttributes.registerate("text.offset");
	_externalAttributes.registerate("text.scale");
	_externalAttributes.registerate("text.colorMix");
	_externalAttributes.registerate("text.binded");

	_externalAttributes.registerate("meshPosition");

	_externalAttributes.registerate("material.color");
	_externalAttributes.registerate("material.diffuse");
	_externalAttributes.registerate("material.specular");
	_externalAttributes.registerate("material.hardness");
}


void DiffuseShader::_passInternalAttributes()
{
}
