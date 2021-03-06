#include <iomanip>
#include "imagepng.h"


ImagePNG::ImagePNG(const std::string &filename)
	: super(filename)
{
}


ImagePNG::ImagePNG(int width, int height)
	: super(width, height)
{
}


ImagePNG::ImagePNG(const ImagePNG &img)
	: super(img.get_width(), img.get_height())
{
	this->m_info = img.m_info;
	this->m_pixbuf = img.m_pixbuf;

	std::cout << "Image Copy-constructor." << std::endl;
}


ImagePNG::ImagePNG(const ImagePNG &&img)
	: super(img.get_width(), img.get_height())
{
	this->m_info = std::move(img.m_info);
	this->m_pixbuf = std::move(img.m_pixbuf);

	std::cout << "Image Move-constructor." << std::endl;
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
	return ++iterator(get_width()-1, get_height()-1, this);
}


ImagePNG::const_iterator ImagePNG::begin() const
{
	return const_iterator(0, 0, this);
}


ImagePNG::const_iterator ImagePNG::end() const
{
	return ++const_iterator(get_width()-1, get_height()-1, this);
}


ImagePNG::const_iterator ImagePNG::cbegin() const
{
	return const_iterator(0, 0, this);
}


ImagePNG::const_iterator ImagePNG::cend() const
{
	return ++const_iterator(get_width()-1, get_height()-1, this);
}


size_t ImagePNG::get_size() const
{
	return (get_width() * get_height());
}


ImagePNG::iterator::iterator()
	: _num(0),
	  _container(nullptr)
{
}


ImagePNG::iterator::iterator(int x, int y, ImagePNG *container)
	: _num(x + (y * container->get_width())),
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


ImagePNG::pixel_t ImagePNG::iterator::operator*()
{
	return _container->get_pixel(get_x(), get_y());
}


ImagePNG::iterator &ImagePNG::iterator::operator=(const ImagePNG::iterator &it)
{
	_num = it._num;
	_container = it._container;

	return (*this);
}


ImagePNG::iterator &ImagePNG::iterator::operator=(const ImagePNG::pixel_t &p)
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


ImagePNG::iterator &ImagePNG::iterator::operator--()
{
	--_num;
	return (*this);
}


ImagePNG::iterator ImagePNG::iterator::operator--(int)
{
	iterator it = (*this);
	this->operator--();

	return it;
}


bool ImagePNG::iterator::is_valid() const
{
	int x = get_x();
	int y = get_y();

	return ((x >= 0)
			&& (y >= 0)
			&& (x < int(_container->get_width()))
			&& (y < int(_container->get_height())));
}


int ImagePNG::iterator::get_x() const
{
	// Returns column's num.
	return (_num % (_container->get_width()));
}


int ImagePNG::iterator::get_y() const
{
	// Returns row's num.
	return (_num / (_container->get_width()));
}


size_t ImagePNG::iterator::get_num() const
{
	return _num;
}


ImagePNG &ImagePNG::iterator::get_container()
{
	return (*_container);
}


const ImagePNG &ImagePNG::iterator::get_container() const
{
	return (*_container);
}


ImagePNG::const_iterator::const_iterator()
	: _num(0),
	  _container(nullptr)
{
}


ImagePNG::const_iterator::const_iterator(int x, int y, const ImagePNG *container)
	: _num(x + (y * container->get_width())),
	  _container(container)
{
}


ImagePNG::const_iterator::const_iterator(const ImagePNG::const_iterator &it)
	: _num(it._num),
	  _container(it._container)
{
}


ImagePNG::const_iterator::const_iterator(const ImagePNG::const_iterator &&it)
	: _num(std::move(it._num)),
	  _container(std::move(it._container))
{
}


ImagePNG::const_iterator::~const_iterator()
{
}


bool ImagePNG::const_iterator::operator==(const ImagePNG::const_iterator &it) const
{
	return (_num == it._num);
}


bool ImagePNG::const_iterator::operator!=(const ImagePNG::const_iterator &it) const
{
	return (!((*this) == it));
}


const ImagePNG::pixel_t ImagePNG::const_iterator::operator*() const
{
	return _container->get_pixel(get_x(), get_y());
}


ImagePNG::const_iterator &ImagePNG::const_iterator::operator=(const ImagePNG::const_iterator &it)
{
	_num = it._num;
	_container = it._container;

	return (*this);
}


ImagePNG::const_iterator &ImagePNG::const_iterator::operator++()
{
	++_num;
	return (*this);
}


ImagePNG::const_iterator ImagePNG::const_iterator::operator++(int)
{
	const_iterator it = (*this);
	this->operator++();

	return it;
}


ImagePNG::const_iterator &ImagePNG::const_iterator::operator--()
{
	--_num;
	return (*this);
}


ImagePNG::const_iterator ImagePNG::const_iterator::operator--(int)
{
	const_iterator it = (*this);
	this->operator--();

	return it;
}


bool ImagePNG::const_iterator::is_valid() const
{
	const size_t width = _container->get_width();
	const size_t height = _container->get_height();

	return ((_num < (width * height))
			&& (get_x() < int(width))
			&& (get_y() < int(height)));
}


int ImagePNG::const_iterator::get_x() const
{
	// Returns column's num.
	return (_num % (_container->get_width()));
}


int ImagePNG::const_iterator::get_y() const
{
	// Returns row's num.
	return (_num / (_container->get_width()));
}


size_t ImagePNG::const_iterator::get_num() const
{
	return _num;
}


const ImagePNG &ImagePNG::const_iterator::get_container() const
{
	return (*_container);
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


std::ostream &operator<<(std::ostream &out, const ImagePNG::iterator &it)
{
	out << "(" << it.get_num() << " : " << it.get_x() << ", " << it.get_y() << ")";
	return out;
}


std::ostream &operator<<(std::ostream &out, const ImagePNG::const_iterator &it)
{
	out << "(" << it.get_num() << " : " << it.get_x() << ", " << it.get_y() << ")";
	return out;
}
