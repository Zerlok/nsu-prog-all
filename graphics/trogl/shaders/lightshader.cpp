#include "lightshader.hpp"


#include <logger.hpp>
#include "common/utils.hpp"


logger_t moduleLogger = loggerModule(loggerLDebug, loggerDFull);


LightShader::LightShader()
	: Shader("Light Shader")
{
	_setAttributes({"position"});
	_loadSubprograms({Shader::pathTo("light.vs"), Shader::pathTo("light.fs")});
	logDebug << getName() << " created." << logEndl;
}


LightShader::~LightShader()
{
	logDebug << getName() << " removed." << logEndl;
}


void LightShader::passLight(const Light* light) const
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


void LightShader::passComponent(const Component* comp) const
{
	const Object::Type& type = comp->getType();

	if (type == "LIGHT")
		passLight((Light*)comp);
}


void LightShader::passTextures(const Textures& textures) const
{
//	size_t idx = 0;
//	for (const TexturePtr& texture : textures)
//	{
//		_uniforms.passEl("samples[]", idx, texture->getSamplerId());
//		_uniforms.passEl("textures[].offset", idx, texture->getUVOffset());
//		_uniforms.passEl("textures[].scale", idx, texture->getUVScale());
//		_uniforms.passEl("textures[].color", idx, texture->getColorMix());
//		_uniforms.passEl("textures[].normal", idx, texture->getNormal());

//		++idx;
//	}

//	_uniforms.pass("texturesLen", int(textures.size()));
}


void LightShader::_registerUniforms()
{
	logDebug << "Registering " << getName() << " uniforms..." << logEndl;

	_uniforms.registerate("lamp.type");
	_uniforms.registerate("lamp.power");
	_uniforms.registerate("lamp.color");
	_uniforms.registerate("lamp.position");
	_uniforms.registerate("lamp.direction");
	_uniforms.registerate("lamp.ia");
	_uniforms.registerate("lamp.oa");

//	static const size_t maxTexturesLen = 16; // TODO: get this const from shader source code.
//	_uniforms.registerateArray("samples[]", maxTexturesLen);
//	_uniforms.registerateArray("textures[].offset", maxTexturesLen);
//	_uniforms.registerateArray("textures[].scale", maxTexturesLen);
//	_uniforms.registerateArray("textures[].color", maxTexturesLen);
//	_uniforms.registerateArray("textures[].normal", maxTexturesLen);
//	_uniforms.registerate("texturesLen");

//	_uniforms.registerate("texturesMixing");
}


void LightShader::_passInternalUniforms()
{
}
