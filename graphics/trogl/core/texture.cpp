#include "texture.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLDebug, loggerDFull);


int Texture::textureIDs = 0;


Texture::Texture(const std::string& name)
	: Component(Component::Type::TEXTURE, name),
	  _id(textureIDs++),
	  _glTexture(0),
	  _uvOffset(0.0f, 0.0f),
	  _uvScale(1.0f, 1.0f),
	  _colorMix(0.5f),
	  _normal(0.0f),
	  _filtering(Filtering::NONE),
	  _wrapping(Wrapping::REPEATING),
	  _useMipmaps(false)
{
	logDebug << getName() << " texture created." << logEndl;
}


Texture::~Texture()
{
	unbind();
	glDeleteTextures(1, &_glTexture);
	_glTexture = 0;

	logDebug << getName() << " texture removed." << logEndl;
}


const int& Texture::getSamplerId() const
{
	return _id;
}


const glm::vec2& Texture::getUVOffset() const
{
	return _uvOffset;
}


const glm::vec2& Texture::getUVScale() const
{
	return _uvScale;
}


const float& Texture::getColorMix() const
{
	return _colorMix;
}


const float& Texture::getNormal() const
{
	return _normal;
}


void Texture::setUVOffset(const glm::vec2& offset)
{
	_uvOffset = offset;
}


void Texture::setUVScale(const glm::vec2& scale)
{
	_uvScale = scale;
}


void Texture::setColorMix(const float& mixing)
{
	_colorMix = mixing;
}


void Texture::setNormal(const float& normal)
{
	_normal = normal;
}


void Texture::setFiltering(const Texture::Filtering& type)
{
	_useMipmaps = ((type == Filtering::TRILINEAR) || (type == Filtering::ANISOTROPHIC));
	_filtering = type;
}


void Texture::setWrapping(const Texture::Wrapping& type)
{
	_wrapping = type;
}


void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0 + _id);
	glBindTexture(GL_TEXTURE_2D, _glTexture);
}


void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::generate()
{
	create();

	if (_useMipmaps)
		glGenerateMipmap(GL_TEXTURE_2D);

	_setupGLTexture();

	logDebug << getName() << " generated." << logEndl;
}


void Texture::create()
{
	if (_glTexture != 0)
		return;

	glGenTextures(1, &_glTexture);
}


void Texture::_setupGLTexture()
{
	GLuint wrapping;
	GLuint filtering;

	switch (_wrapping)
	{
		case Texture::Wrapping::MIRRORED_REPEATING:
			wrapping = GL_MIRRORED_REPEAT;
			break;
		case Texture::Wrapping::EDGE_CLAMPING:
			wrapping = GL_CLAMP_TO_EDGE;
			break;
		case Texture::Wrapping::BORDER_CLAMPING:
			wrapping = GL_CLAMP_TO_BORDER;
			break;
		case Texture::Wrapping::REPEATING:
		default:
			wrapping = GL_REPEAT;
			break;
	}

	if (_filtering == Filtering::ANISOTROPHIC)
		filtering = 0;
	else if (_filtering == Filtering::TRILINEAR)
		filtering = GL_LINEAR_MIPMAP_LINEAR;
	else if (_filtering == Filtering::BILINEAR)
		filtering = GL_LINEAR;
	else
		filtering = GL_NEAREST;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);
}
