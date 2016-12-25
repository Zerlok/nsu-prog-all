#include "imagetexture.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


ImageTexture::ImageTexture(const std::string& filename)
	: Texture(filename),
	  _image(filename.c_str())
{
	if (_image.isNull())
		logWarning << "Failed to load image from file: " << filename << logEndl;
	else
		logDebug << getName() << " texture loaded from image ("
				 << _image.width() << 'x' << _image.height()
				 << ')'
				 << logEndl;
}


ImageTexture::~ImageTexture()
{
	logDebug << getName() << " image texutre removed." << logEndl;
}


void ImageTexture::generate()
{
	_create();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _image.width(), _image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _image.bits());
	Texture::generate();

	logDebug << getName() << " generated." << logEndl;
}

