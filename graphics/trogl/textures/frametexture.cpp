#include "frametexture.hpp"


FrameTexture::FrameTexture(const size_t& width,
						   const size_t& height)
	: Texture("frame-texture"),
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

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	Texture::generate();
}
