#include "image.hpp"


Image::Image()
	: QImage()
{
}


Image::Image(const size_t& width, const size_t& height)
	: QImage(width, height, QImage::Format_RGBA8888)
{
}


Image::~Image()
{
}


Image Image::resize(const size_t& width, const size_t& height)
{
	Image resized(width, height);

	const float wr = float(this->width()) / float(width);
	const float hr = float(this->height()) / float(height);
	const float pxArea = wr * hr;

	for (size_t v = 0; v < height; ++v)
		for (size_t u = 0; u < width; ++u)
			resized.setPixel(u, v, pixel(u * wr, v * hr));

	return resized;
}
