#include "image.hpp"


Image::Image(const Format& format)
	: _format(format),
	  _width(0),
	  _height(0),
	  _data()
{
}


Image::Image(std::istream& in, const Image::Format& format)
	: _format(format),
	  _width(0),
	  _height(0),
	  _data()
{
	load(in);
}


Image::Image(const Image& img)
	: _format(img._format),
	  _width(img._width),
	  _height(img._height),
	  _data(img._data)
{
}


Image::Image(Image&& img)
	: _format(std::move(img._format)),
	  _width(std::move(img._width)),
	  _height(std::move(img._height)),
	  _data(std::move(img._data))
{
}


Image::~Image()
{
}


Image& Image::operator=(const Image& img)
{
	_format = img._format;
	_width = img._width;
	_height = img._height;
	_data = img._data;
}


Image& Image::operator=(Image&& img)
{
	_format = std::move(img._format);
	_width = std::move(img._width);
	_height = std::move(img._height);
	_data = std::move(img._data);

	return (*this);
}


bool Image::isEmpty() const
{
	return ((_data.get() == nullptr)
			|| (_data.get()->empty()));
}


const Image::Format& Image::getFormat() const
{
	return _format;
}


const size_t& Image::getWidth() const
{
	return _width;
}


const size_t& Image::getHeight() const
{
	return _height;
}


const size_t& Image::getPixelsCount() const
{
	return _data->size();
}


const size_t& Image::getPixelsSize() const
{
	return (_data->size() * sizeof(Pixel));
}


void Image::setFormat(const Image::Format& format)
{
	_format = format;
}


bool Image::load(std::istream& in)
{
	// TODO: load JPG, PNG, BMP.
	switch (_format)
	{
		case Format::JPG:
			return _loadJPGImage(in, *this);
		case Format::PNG:
			return _loadPNGImage(in, *this);
		case Format::BMP:
			return _loadBMPImage(in, *this);
		default:
			return false;
	}
}


bool Image::save(std::ostream& out) const
{

}


Image Image::copy() const
{

}


Image Image::scale(const size_t& width, const size_t& height) const
{

}


bool Image::_loadJPGImage(std::istream& in, Image& img)
{
	return true;
}


bool Image::_loadPNGImage(std::istream& in, Image& img)
{
	return true;
}


bool Image::_loadBMPImage(std::istream& in, Image& img)
{
	return true;
}

