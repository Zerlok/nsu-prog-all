#include "squaredwbtexture.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLDebug, loggerDFull);


const SquaredWBTexture::PixelRGB SquaredWBTexture::whitePixel = {1.0f, 1.0f, 1.0f};
const SquaredWBTexture::PixelRGB SquaredWBTexture::blackPixel = {0.0f, 0.0f, 0.0f};


SquaredWBTexture::SquaredWBTexture(const size_t& width,
								   const size_t& height)
	: Texture("WAB"),
	  _width(width),
	  _height(height),
	  _pixels((_width * _height * 3), 0.0f)
{
	size_t i = 0;
	for (size_t y = 0; y < _height; ++y)
	{
		for (size_t x = 0; x < _width; ++x)
		{
			if (((x+y) % 2) == 0)
			{
				_pixels[i] = whitePixel.r;
				_pixels[i+1] = whitePixel.g;
				_pixels[i+2] = whitePixel.b;
			}

			i += 3;
		}
	}

	logDebug << getName() << " squared texture ("
			 << _width << 'x' << _height << ") created."
			 << logEndl;
}


SquaredWBTexture::~SquaredWBTexture()
{
	logDebug << getName() << " squared texture removed." << logEndl;
}


void SquaredWBTexture::generate()
{
	_create();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_FLOAT, _pixels.data());
	Texture::generate();

	logDebug << getName() << " squared texture generated." << logEndl;
}
