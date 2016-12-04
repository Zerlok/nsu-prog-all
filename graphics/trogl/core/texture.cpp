#include "texture.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


Texture::Texture(const std::string& filename)
	: Component(Component::Type::TEXTURE, filename),
	  _uvOffset(0.0f, 0.0f),
	  _colorMix(0.5f),
	  _normal(0.0f),
	  _image(filename.c_str())
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


void Texture::generate()
{
	glGenTextures(1, &_glTexture);
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _image.width(), _image.height(), 0, GL_RGB, GL_FLOAT, _image.bits());
	unbind();
}


void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, _glTexture);
}


void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
