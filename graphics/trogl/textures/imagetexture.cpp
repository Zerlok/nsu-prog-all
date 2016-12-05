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
			 << ", px(0, 0): " << _image.pixel(0, 0)
			 << logEndl;
}


ImageTexture::~ImageTexture()
{
	logDebug << getName() << " image texutre removed." << logEndl;
}


void ImageTexture::generate()
{
	Texture::generate();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _image.width(), _image.height(), 0, GL_RGB, GL_UNSIGNED_INT, _image.bits());
	unbind();

	logDebug << getName() << " generated." << logEndl;
}

