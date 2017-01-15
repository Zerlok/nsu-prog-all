#include "color.hpp"


#include <utility>


const Color Color::transparent = Color(0, 0, 0, 0);
const Color Color::white = Color(255, 255, 255);
const Color Color::grey = Color(128, 128, 128);
const Color Color::black = Color(0, 0, 0);
const Color Color::red = Color(255, 0, 0);
const Color Color::green = Color(0, 255, 0);
const Color Color::blue = Color(0, 0, 255);


Color Color::makeRGB(const int& r,
					 const int& g,
					 const int& b)
{
	return std::move(Color(r, g, b));
}


Color Color::makeRGBA(const int& r,
					  const int& g,
					  const int& b,
					  const int& a)
{
	return std::move(Color(r, g, b, a));
}


Color Color::makeHSV(const int& h,
					 const int& s,
					 const int& v)
{
	int r;
	int g;
	int b;

	unsigned char region, remainder, p, q, t;

	if (s == 0)
	{
		r = v;
		g = v;
		b = v;
		return std::move(Color(r, g, b));
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


Color::Color(const int& red,
			 const int& green,
			 const int& blue,
			 const int& alpha)
	: _red(red),
	  _green(green),
	  _blue(blue),
	  _alpha(alpha)
{
}


Color::Color(const Color& c)
	: _red(c._red),
	  _green(c._green),
	  _blue(c._blue),
	  _alpha(c._alpha)
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


Color& Color::operator+=(const Color& c)
{
	_red += c._red;
	_green += c._green;
	_blue += c._blue;
	_alpha += c._alpha;

	return (*this);
}


Color& Color::operator*=(const float& ratio)
{
	_red *= ratio;
	_green *= ratio;
	_blue *= ratio;
	_alpha *= ratio;

	return (*this);
}


Color Color::operator+(const Color& c) const
{
	Color tmp(*this);
	tmp += c;

	return std::move(tmp);
}


Color Color::operator*(const float& ratio) const
{
	Color tmp(*this);
	tmp *= ratio;

	return std::move(tmp);
}


const int& Color::getRed() const
{
	return _red;
}


const int& Color::getGreen() const
{
	return _green;
}


const int& Color::getBlue() const
{
	return _blue;
}


const int& Color::getAlpha() const
{
	return _alpha;
}


float Color::getRedF() const
{
	return float(_red % 256) / 255.0f;
}


float Color::getGreenF() const
{
	return float(_green % 256) / 255.0f;
}


float Color::getBlueF() const
{
	return float(_blue % 256) / 255.0f;
}


float Color::getAlphaF() const
{
	return float(_alpha % 256) / 255.0f;
}
