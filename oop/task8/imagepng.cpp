#include <iomanip>
#include "imagepng.h"


ImagePNG::ImagePNG(const std::string &filename)
	: super(filename)
{
}


ImagePNG::~ImagePNG()
{
}


ImagePNG::iterator ImagePNG::begin()
{
	return iterator(0, 0, this);
}


ImagePNG::iterator ImagePNG::end()
{
	return iterator(0, get_height(), this);
}


ImagePNG::iterator::iterator()
	: _num(0),
	  _container(nullptr)
{
}


ImagePNG::iterator::iterator(int x, int y, ImagePNG *container)
	: _num(x + y * (container->get_width())),
	  _container(container)
{
}


ImagePNG::iterator::iterator(const ImagePNG::iterator &it)
	: _num(it._num),
	  _container(it._container)
{
}


ImagePNG::iterator::iterator(const ImagePNG::iterator &&it)
	: _num(std::move(it._num)),
	  _container(std::move(it._container))
{
}


ImagePNG::iterator::~iterator()
{
}


bool ImagePNG::iterator::operator==(const ImagePNG::iterator &it) const
{
	return (_num == it._num);
}


bool ImagePNG::iterator::operator!=(const ImagePNG::iterator &it) const
{
	return (!((*this) == it));
}


ImagePNG::pixel ImagePNG::iterator::operator*()
{
	return _container->get_pixel(get_x(), get_y());
}


ImagePNG::iterator &ImagePNG::iterator::operator=(const ImagePNG::iterator &it)
{
	_num = it._num;
	_container = it._container;

	return (*this);
}


ImagePNG::iterator &ImagePNG::iterator::operator=(const ImagePNG::pixel &p)
{
	_container->set_pixel(get_x(), get_y(), p);
	return (*this);
}


ImagePNG::iterator &ImagePNG::iterator::operator++()
{
	++_num;
	return (*this);
}


ImagePNG::iterator ImagePNG::iterator::operator++(int)
{
	iterator it = (*this);
	this->operator++();

	return it;
}


int ImagePNG::iterator::get_x() const
{
	return (_num % (_container->get_width()));
}


int ImagePNG::iterator::get_y() const
{
	return (_num / (_container->get_height()));
}


std::ostream &operator<<(std::ostream &out, const png::gray_pixel &p)
{
	return out << png::rgb_pixel(p, p, p);
}


std::ostream &operator<<(std::ostream &out, const png::rgb_pixel &p)
{
	out << "0x" << std::hex << std::setfill('0')
		<< std::setw(2) << int(p.red)
		<< std::setw(2) << int(p.green)
		<< std::setw(2) << int(p.blue);

	return out << std::dec;
}
