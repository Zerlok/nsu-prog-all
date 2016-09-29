#include "types.hpp"


const unsigned char Color::COLOR_DEPTH = 256;


Color Color::makeRGB(const unsigned char& r,
					 const unsigned char& g,
					 const unsigned char& b)
{
	return std::move(Color(r, g, b));
}


Color Color::makeRGBA(const unsigned char& r,
					  const unsigned char& g,
					  const unsigned char& b,
					  const unsigned char& a)
{
	return std::move(Color(r, g, b, a));
}


Color Color::makeHSV(const unsigned char& h,
					 const unsigned char& s,
					 const unsigned char& v)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	unsigned char region, remainder, p, q, t;

	if (s == 0)
	{
		r = v;
		g = v;
		b = v;
		return rgb;
	}

	region = h / 43;
	remainder = (h - (region * 43)) * 6;

	p = (v * (255 - s)) >> 8;
	q = (v * (255 - ((s * remainder) >> 8))) >> 8;
	t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

	switch (region)
	{
		case 0:
			r = v; g = t; b = p;
			break;
		case 1:
			r = q; g = v; b = p;
			break;
		case 2:
			r = p; g = v; b = t;
			break;
		case 3:
			r = p; g = q; b = v;
			break;
		case 4:
			r = t; g = p; b = v;
			break;
		default:
			r = v; g = p; b = q;
			break;
	}

	return std::move(Color(r, g, b));
}


Color::Color(const unsigned char& red,
			 const unsigned char& green,
			 const unsigned char& blue,
			 const unsigned char& alpha)
	: _red(red), _green(green), _blue(blue), _alpha(alpha)
{
}


Color::Color(const Color& c)
	: _red(c._red), _green(c._green), _blue(c._blue), _alpha(c._alpha)
{
}


Color::Color(Color&& c)
	: _red(std::move(c._red)),
	  _green(std::move(c._green)),
	  _blue(std::move(c._blue)),
	  _alpha(std::move(c._alpha))
{
}


Color::~Color()
{
}


Color& Color::operator=(const Color& c)
{
	_red = c._red;
	_green = c._green;
	_blue = c._blue;
	_alpha = c._alpha;

	return (*this);
}


Color& Color::operator=(Color&& c)
{
	_red = std::move(c._red);
	_green = std::move(c._green);
	_blue = std::move(c._blue);
	_alpha = std::move(c._alpha);

	return (*this);
}


const unsigned char& Color::getRed() const
{
	return _red;
}


const unsigned char& Color::getGreen() const
{
	return _green;
}


const unsigned char& Color::getBlue() const
{
	return _blue;
}


const unsigned char& Color::getAlpha() const
{
	return _alpha;
}
