#include "frametexture.hpp"


FrameTexture::FrameTexture(const Type& type,
						   const size_t& width,
						   const size_t& height)
	: Texture("frame-texture"),
	  _type(type),
	  _width(width),
	  _height(height)
{
	setFiltering(Filtering::NONE);
	setWrapping(Wrapping::EDGE_CLAMPING);
}


FrameTexture::~FrameTexture()
{
}


const GLuint& FrameTexture::getBuffId() const
{
	return _glTexture;
}


void FrameTexture::generate()
{
	_create();

	switch (_type)
	{
		case Type::COLOR:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
			break;

		case Type::DEPTH:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, _width, _height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
			break;
	}

	Texture::generate();
}
