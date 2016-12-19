#include "imagetexture.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLDebug, loggerDFull);


ImageTexture::ImageTexture(const std::string& filename)
	: Texture(filename),
	  _image(filename.c_str())
{
	logDebug << getName() << " image texture created ("
			 << "null: " << _image.isNull()
			 << ", size: " << _image.width() << 'x' << _image.height()
			 << ')'
			 << logEndl;
}


ImageTexture::~ImageTexture()
{
	logDebug << getName() << " image texutre removed." << logEndl;
}


void ImageTexture::generate()
{
	create();
	bind();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _image.width(), _image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _image.bits());
	Texture::generate();

	unbind();

	logDebug << getName() << " generated." << logEndl;
}

