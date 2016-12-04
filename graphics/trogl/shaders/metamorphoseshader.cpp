#include "metamorphoseshader.hpp"


#include <logger.hpp>
#include "common/utils.hpp"


logger_t moduleLogger = loggerModule(loggerLWarning,
										 loggerDFull);


const std::string MetamorphoseShader::VS_FILE = path::join(Shader::SRC_DIR, "metamorph.vs");


MetamorphoseShader::MetamorphoseShader()
	: Shader("Metamorph Shader", {VS_FILE, DEFAULT_FS_FILE})
{
	logDebug << "Metamorph Shader created" << std::endl;
}


MetamorphoseShader::~MetamorphoseShader()
{
}


void MetamorphoseShader::_registerAttributes()
{
	_attrObjPosition = glGetUniformLocation(_glShader, "meshPosition");
	_attrCosSqAlpha = glGetUniformLocation(_glShader, "cosSqAlpha");
}


void MetamorphoseShader::_passInternalAttributes()
{
	glUniform1f(_attrCosSqAlpha, std::pow(std::cos(getTimeDouble() / 10.0), 2));
}


void MetamorphoseShader::passComponent(const Component* comp)
{
	if ((comp == nullptr)
			|| (comp->getType() != Component::Type::OBJECT))
		return;

	passObject((Object*)comp);
}


void MetamorphoseShader::passObject(Object const* obj)
{
	if ((obj == nullptr)
			|| (obj->getObjectType() != Object::Type::MESH))
		return;

	const glm::vec3& pos = obj->getPosition();
	glUniform3f(_attrObjPosition, pos.x, pos.y, pos.z);
}
