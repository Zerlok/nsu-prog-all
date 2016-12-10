#include "image.hpp"


Image::Image()
	: super()
{
}


Image::Image(const size_t& width, const size_t& height)
	: super(width, height)
{
}


Image::Image(std::istream& in)
	: super(in)
{
}


Image::~Image()
{
}


bool Image::isEmpty() const
{
	return (get_row(0).empty());
}


size_t Image::getWidth() const
{
	return get_width();
}


size_t Image::getHeight() const
{
	return get_height();
}


void Image::load(std::istream& in)
{
	read_stream(in);
}


void Image::save(std::ostream& out)
{
	write_stream<std::ostream>(out);
}


Image Image::resize(const size_t& width, const size_t& height)
{
	Image resized(width, height);

	resized.set_compression_type(get_compression_type());
	resized.set_filter_type(get_filter_type());
	resized.set_interlace_type(get_interlace_type());
	resized.set_palette(get_palette());
	resized.set_tRNS(get_tRNS());

	const float wr = float(get_width()) / float(width);
	const float hr = float(get_height()) / float(height);

	for (size_t y = 0; y < height; ++y)
	{
		for (size_t x = 0; x < width; ++x)
		{
			resized.set_pixel(x, y, get_pixel(x * wr, y * hr));
		}
	}

	return resized;
}

