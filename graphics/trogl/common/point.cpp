#include "point.hpp"

#include <utility>
#include <cmath>


const Point Point::zero = Point(0, 0, 0);


Point::Point(const int& x, const int& y, const int& z)
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


double Point::distance(const Point& p) const
{
	return std::sqrt(std::pow(_x - p._x, 2)
					 + std::pow(_y - p._y, 2)
					 + std::pow(_z - p._z, 2));
}
