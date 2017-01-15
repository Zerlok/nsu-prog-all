#include "diffuseshader.hpp"


#include <logger.hpp>
#include "common/utils.hpp"


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


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
	const Object::Type& type = obj->getType();

	if (type == "MESH")
		passMesh((Mesh*)obj);
	else if (type == "LIGHT")
		passLight((Light*)obj);
	else if (type == "CAMERA")
		passCamera((Camera*)obj);
}


void DiffuseShader::passCamera(const Camera* camera) const
{
	const glm::vec3& pos = camera->getPosition();
	const glm::vec3& dir = camera->getLookingAtPosition();

	_uniforms.pass("camera.position", pos.x, pos.y, pos.z, 1.0f);
	_uniforms.pass("camera.direction", dir.x, dir.y, dir.z, 0.0f);
}


void DiffuseShader::passLight(const Light* light) const
{
	const glm::vec3& pos = light->getPosition();
	const glm::vec3& dir = light->getDirection();

	_uniforms.pass("lamp.type", int(light->getLightType()));
	_uniforms.pass("lamp.power", light->getPower());
	_uniforms.pass("lamp.color", light->getColor());
	_uniforms.pass("lamp.position", pos.x, pos.y, pos.z, 1.0f);
	_uniforms.pass("lamp.direction", dir.x, dir.y, dir.z, 0.0f);
	_uniforms.pass("lamp.ia", light->getInnerAngle());
	_uniforms.pass("lamp.oa", light->getOutterAngle());
}


void DiffuseShader::passMesh(const Mesh* mesh) const
{
	const glm::vec3& pos = mesh->getPosition();

	_uniforms.pass("meshPosition", pos.x, pos.y, pos.z, 1.0f);
}


void DiffuseShader::passComponent(const Component* comp) const
{
	const Object::Type& type = comp->getType();

	if (type == "MESH")
		passMesh((Mesh*)comp);
	else if (type == "LIGHT")
		passLight((Light*)comp);
	else if (type == "CAMERA")
		passCamera((Camera*)comp);
}


void DiffuseShader::passTextures(const Textures& textures) const
{
	size_t idx = 0;
	for (const TexturePtr& texture : textures)
	{
		_uniforms.passEl("samples[]", idx, texture->getSamplerId());
		_uniforms.passEl("textures[].offset", idx, texture->getUVOffset());
		_uniforms.passEl("textures[].scale", idx, texture->getUVScale());
		_uniforms.passEl("textures[].color", idx, texture->getColorMix());
		_uniforms.passEl("textures[].normal", idx, texture->getNormal());

		++idx;
	}

	_uniforms.pass("texturesLen", int(textures.size()));
}


void DiffuseShader::_registerUniforms()
{
	// External.
	_uniforms.registerate("camera.position");
	_uniforms.registerate("camera.direction");

	_uniforms.registerate("lamp.type");
	_uniforms.registerate("lamp.power");
	_uniforms.registerate("lamp.color");
	_uniforms.registerate("lamp.position");
	_uniforms.registerate("lamp.direction");
	_uniforms.registerate("lamp.ia");
	_uniforms.registerate("lamp.oa");

	static const size_t maxTexturesLen = 16; // TODO: get this const from shader source code.
	_uniforms.registerateArray("samples[]", maxTexturesLen);
	_uniforms.registerateArray("textures[].offset", maxTexturesLen);
	_uniforms.registerateArray("textures[].scale", maxTexturesLen);
	_uniforms.registerateArray("textures[].color", maxTexturesLen);
	_uniforms.registerateArray("textures[].normal", maxTexturesLen);
	_uniforms.registerate("texturesLen");

	_uniforms.registerate("meshPosition");

	_uniforms.registerate("material.color");
	_uniforms.registerate("material.diffuse");
	_uniforms.registerate("material.specular");
	_uniforms.registerate("material.hardness");
	_uniforms.registerate("texturesMixing");

	logDebug << getName() << " external attributes registered." << logEndl;
}


void DiffuseShader::_passInternalUniforms()
{
}
