#include "texture.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


int Texture::_activeId = 0;


Texture::Texture(const std::string& name)
	: Animatable("TEXTURE", name),
	  _id(0),
	  _glTexture(0),
	  _uvOffset(0.0f, 0.0f),
	  _uvScale(1.0f, 1.0f),
	  _color(1.0),
	  _normal(0.0),
	  _filtering(Filtering::NONE),
	  _wrapping(Wrapping::REPEATING),
	  _useMipmaps(false)
{
	logDebug << getName() << " texture created." << logEndl;
}


Texture::Texture(const Texture& text)
	: Animatable(text),
	  _id(text._id),
	  _glTexture(text._glTexture),
	  _uvOffset(text._uvOffset),
	  _uvScale(text._uvScale),
	  _color(text._color),
	  _normal(text._normal),
	  _filtering(text._filtering),
	  _wrapping(text._wrapping),
	  _useMipmaps(text._useMipmaps)
{
	logDebug << getName() << " copied from " << text.getName() << logEndl;
}

Texture::Texture(Texture&& text)
	: Animatable(std::move(text)),
	  _id(std::move(text._id)),
	  _glTexture(std::move(text._glTexture)),
	  _uvOffset(std::move(text._uvOffset)),
	  _uvScale(std::move(text._uvScale)),
	  _color(std::move(text._color)),
	  _normal(std::move(text._normal)),
	  _filtering(std::move(text._filtering)),
	  _wrapping(std::move(text._wrapping)),
	  _useMipmaps(std::move(text._useMipmaps))
{
	logDebug << getName() << " texture moved." << logEndl;
}


Texture::~Texture()
{
	unbind();

	if (_glTexture != 0)
	{
		glDeleteTextures(1, &_glTexture);
		_glTexture = 0;
	}

	logDebug << getName() << " texture removed." << logEndl;
}


Texture& Texture::operator=(const Texture& text)
{
	_id = text._id;
	_glTexture = text._glTexture;
	_uvOffset = text._uvOffset;
	_uvScale = text._uvScale;
	_color = text._color;
	_normal = text._normal;
	_filtering = text._filtering;
	_wrapping = text._wrapping;
	_useMipmaps = text._useMipmaps;

	logDebug << getName() << " copied from " << text.getName() << logEndl;
	return (*this);
}


Texture& Texture::operator=(Texture&& text)
{
	_id = text._id;
	_glTexture = text._glTexture;
	_uvOffset = std::move(text._uvOffset);
	_uvScale = std::move(text._uvScale);
	_color = std::move(text._color);
	_normal = std::move(text._normal);
	_filtering = std::move(text._filtering);
	_wrapping = std::move(text._wrapping);
	_useMipmaps = std::move(text._useMipmaps);

	text._id = 0;
	text._glTexture = 0;

	logDebug << getName() << " moved." << logEndl;
	return (*this);
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
	return _color;
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


void Texture::setColorMix(const float& color)
{
	_color = color;
}


void Texture::setNormal(const float& normal)
{
	_normal = normal;
}


void Texture::setFiltering(const Texture::Filtering& type)
{
	_useMipmaps = ((type == Filtering::TRILINEAR) || (type == Filtering::ANISOTROPIC));
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
	if (_glTexture == 0)
		return;

	bind();

	if (_useMipmaps)
		glGenerateMipmap(GL_TEXTURE_2D);

	GLuint wrapping;
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

	GLuint minFiltering;
	GLuint magFiltering;
	if (_filtering == Filtering::ANISOTROPIC)
	{
		float maxAnisotropicLevel;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropicLevel);
		logInfo << "OpenGL anisotropic filtering is supported, max level: " << maxAnisotropicLevel << logEndl;

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropicLevel / 2.0);

		minFiltering = GL_LINEAR_MIPMAP_LINEAR;
		magFiltering = GL_LINEAR;
	}
	else if (_filtering == Filtering::TRILINEAR)
	{
		minFiltering = GL_LINEAR_MIPMAP_LINEAR;
		magFiltering = GL_LINEAR;
	}
	else if (_filtering == Filtering::BILINEAR)
	{
		minFiltering = GL_LINEAR;
		magFiltering = GL_LINEAR;
	}
	else
	{
		minFiltering = GL_NEAREST;
		magFiltering = GL_NEAREST;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFiltering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFiltering);

	unbind();
	logDebug << getName() << " texture filtering, wrapping setup." << logEndl;
}


void Texture::_create()
{
	static int textureID;
	if (_glTexture != 0)
	{
		bind();
		return;
	}

	_id = textureID++;
	glGenTextures(1, &_glTexture);
	bind();
}


void Texture::_regProperties()
{
	_regProperty(_uvOffset);
	_regProperty(_uvScale);
	_regProperty(_color);
	_regProperty(_normal);
}
