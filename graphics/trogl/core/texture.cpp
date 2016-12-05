#include "texture.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLDebug, loggerDFull);


size_t Texture::textureID = 0;


Texture::Texture(const std::string& name)
	: Component(Component::Type::TEXTURE, name),
	  _id(textureID++),
	  _glTexture(0),
	  _uvOffset(0.0f, 0.0f),
	  _colorMix(0.5f),
	  _normal(0.0f)
{
	logDebug << getName() << " texture created." << logEndl;
}


Texture::~Texture()
{
	logDebug << getName() << " texture removed." << logEndl;
}


const glm::vec2& Texture::getUVOffset() const
{
	return _uvOffset;
}


const float& Texture::getColorMix() const
{
	return _colorMix;
}


const float& Texture::getNormal() const
{
	return _normal;
}


const size_t& Texture::getSampler() const
{
	return _id;
}


void Texture::generate()
{
	if (_glTexture != 0)
		return;

	glGenTextures(1, &_glTexture);
	bind();

	logDebug << getName() << " generated." << logEndl;
}


void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, _glTexture);
	glActiveTexture(GL_TEXTURE0 + _id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

//	logDebug << getName() << " binded." << logEndl;
}


void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
