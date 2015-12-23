#include "affinetransformation.h"


AffineTransformation::AffineTransformation(
		const double a00,
		const double a01,
		const double a10,
		const double a11,
		const double b0,
		const double b1)
	: _a00(a00),
	  _a01(a01),
	  _a10(a10),
	  _a11(a11),
	  _b0(b0),
	  _b1(b1)
{
}


AffineTransformation::AffineTransformation(const AffineTransformation &tr)
	: _a00(tr._a00),
	  _a01(tr._a01),
	  _a10(tr._a10),
	  _a11(tr._a11),
	  _b0(tr._b0),
	  _b1(tr._b1)
{
}


AffineTransformation::~AffineTransformation()
{
}


void AffineTransformation::transform(double &x, double &y) const
{
	const double transformed_x = (_a00 * x + _a01 * y) + _b0;
	const double transformed_y = (_a10 * x + _a11 * y) + _b1;

	x = transformed_x;
	y = transformed_y;
}


AffineTransformation &AffineTransformation::operator=(const AffineTransformation &tr)
{
	_a00 = tr._a00;
	_a01 = tr._a01;
	_a10 = tr._a10;
	_a11 = tr._a11;
	_b0 = tr._b0;
	_b1 = tr._b1;

	return (*this);
}


AffineTransformation AffineTransformation::operator+(const AffineTransformation &tr)
{
	AffineTransformation ntr(*this);
	return (ntr += tr);
}


AffineTransformation &AffineTransformation::operator+=(const AffineTransformation &tr)
{
	// Multiply A matricies.
	const double a00 = _a00 * tr._a00 + _a01 * tr._a10;
	const double a01 = _a00 * tr._a01 + _a01 * tr._a11;
	const double a10 = _a10 * tr._a00 + _a11 * tr._a10;
	const double a11 = _a10 * tr._a01 + _a11 * tr._a11;

	_a00 = a00;
	_a01 = a01;
	_a10 = a10;
	_a11 = a11;

	// Sum B vectors.
	_b0 += tr._b0;
	_b1 += tr._b1;

	return (*this);
}


TranslationTransformation::TranslationTransformation(const int dx, const int dy)
	: AffineTransformation(1.0, 0.0, 0.0, 1.0, double(dx), double(dy))
{
}


TranslationTransformation::TranslationTransformation(const double dx, const double dy)
	: AffineTransformation(1.0, 0.0, 0.0, 1.0, dx, dy)
{
}


TranslationTransformation::TranslationTransformation(const TranslationTransformation &tr)
	: AffineTransformation(tr)
{
}


double RotationTransformation::get_radians(const int degrees)
{
	return (RotationTransformation::radian * degrees);
}


const double RotationTransformation::round_ratio = 1000.0;
const double RotationTransformation::radian = (M_PI / 180);


RotationTransformation::RotationTransformation(const int degrees)
{
	const double radians = get_radians(degrees);
	_a00 = round(cos(radians) * round_ratio) / round_ratio;
	_a10 = round(sin(radians) * round_ratio) / round_ratio;
	_a01 = -_a10;
	_a11 = _a00;
}


RotationTransformation::RotationTransformation(const double radians)
{
	_a00 = round(cos(radians) * round_ratio) / round_ratio;
	_a10 = round(sin(radians) * round_ratio) / round_ratio;
	_a01 = -_a10;
	_a11 = _a00;
}


RotationTransformation::RotationTransformation(const RotationTransformation &tr)
	: AffineTransformation(tr)
{
}


ScalingTransformation::ScalingTransformation(const int sx, const int sy)
	: AffineTransformation(double(sx), 0.0, 0.0, double(sy))
{
}


ScalingTransformation::ScalingTransformation(const double sx, const double sy)
	: AffineTransformation(sx, 0.0, 0.0, sy)
{
}


ScalingTransformation::ScalingTransformation(const ScalingTransformation &tr)
	: AffineTransformation(tr)
{
}
