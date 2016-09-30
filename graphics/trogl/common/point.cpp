#include "point.hpp"

#include <utility>
#include <cmath>


const Point Point::zero = Point(0, 0, 0);
const Point Point::one = Point(1, 1, 1);


Point::Point(const float& x, const float& y, const float& z)
	: _x(x), _y(y), _z(z)
{
}


Point::Point(const Point& p)
	: _x(p._x), _y(p._y), _z(p._z)
{
}


Point::Point(Point&& p)
	: _x(std::move(p._x)), _y(std::move(p._y)), _z(std::move(p._z))
{
}


Point::~Point()
{
}


Point& Point::operator=(const Point& p)
{
	_x = p._x;
	_y = p._y;
	_z = p._z;

	return (*this);
}


Point& Point::operator=(Point&& p)
{
	_x = std::move(p._x);
	_y = std::move(p._y);
	_z = std::move(p._z);

	return (*this);
}


bool Point::operator==(const Point& p) const
{
	return ((_x == p._x)
			&& (_y == p._y)
			&& (_z == p._z));
}


bool Point::operator!=(const Point& p) const
{
	return (!this->operator==(p));
}


Point& Point::operator+=(const Point& p)
{
	_x += p._x;
	_y += p._y;
	_z += p._z;

	return (*this);
}


Point Point::operator+(const Point& p) const
{
	Point tmp(*this);
	tmp += p;

	return tmp;
}


Point& Point::operator-=(const Point& p)
{
	_x -= p._x;
	_y -= p._y;
	_z -= p._z;

	return (*this);
}


Point Point::operator-(const Point& p) const
{
	Point tmp(*this);
	tmp -= p;

	return tmp;
}


double Point::distance(const Point& p) const
{
	return std::sqrt(std::pow(_x - p._x, 2)
					 + std::pow(_y - p._y, 2)
					 + std::pow(_z - p._z, 2));
}


Point Point::crossProduct(const Point& p) const
{
	return std::move(Point((_y * p._z) - (_z * p._y),
						   (_z * p._x) - (_x * p._z),
						   (_x * p._y) - (_y * p._x)));
}


double Point::dotProduct(const Point& p) const
{
	return (_x * p._x + _y * p._y, _z * p._z);
}
