#include "math.h"
#include "point.h"


const Point Point::zero = Point(0, 0);


Point::Point(int x, int y)
	: _x(x), _y(y)
{
}


Point::Point(int cordinates[2])
	: _x(cordinates[0]), _y(cordinates[1])
{
}


Point::Point(const Point &point)
	: _x(point._x), _y(point._y)
{
}


Point::Point(Point &&point)
	: _x(std::move(point._x)), _y(std::move(point._y))
{
}


Point::~Point()
{
}


int Point::get_x() const
{
	return _x;
}


int Point::get_y() const
{
	return _y;
}


double Point::distance_to(const Point &point) const
{
	return sqrt(pow((_x - point._x), 2) + pow((_y - point._y), 2));
}


Point &Point::operator=(const Point &point)
{
	_x = point._x;
	_y = point._y;

	return (*this);
}


Point &Point::operator=(int coordinates[2])
{
	_x = coordinates[0];
	_y = coordinates[1];

	return (*this);
}



bool Point::operator==(const Point &point) const
{
	return ((_x == point._x)
			&& (_y == point._y));
}


bool Point::operator!=(const Point &point) const
{
	return !(this->operator==(point));
}


bool Point::operator==(int coordinates[2]) const
{
	return ((_x == coordinates[0])
			&& (_y == coordinates[2]));
}


bool Point::operator!=(int coordinates[2]) const
{
	return !((*this) == coordinates);
}


bool Point::operator<(const Point &point) const
{
	return ((_x < point._x)
			&& (_y < point._y));
}


bool Point::operator>(const Point &point) const
{
	return ((_x > point._x)
			&& (_y > point._y));
}


bool Point::operator<(int coordinates[2]) const
{
	return ((_x < coordinates[0])
			&& (_y < coordinates[1]));
}


bool Point::operator>(int coordinates[2]) const
{
	return ((_x > coordinates[0])
			&& (_y > coordinates[1]));
}


bool Point::operator<=(const Point &point) const
{
	return ((_x <= point._x)
			&& (_y <= point._y));
}


bool Point::operator>=(const Point &point) const
{
	return ((_x >= point._x)
			&& (_y >= point._y));
}


bool Point::operator<=(int coordinates[2]) const
{
	return ((_x <= coordinates[0])
			&& (_y <= coordinates[1]));
}


bool Point::operator>=(int coordinates[2]) const
{
	return ((_x >= coordinates[0])
			&& (_y >= coordinates[1]));
}


Point Point::operator+(const Point &point) const
{
	return Point((_x + point._x), (_y + point._y));
}


Point Point::operator-(const Point &point) const
{
	return Point((_x - point._x), (_y - point._y));
}


Point &Point::operator+=(const Point &point)
{
	_x += point._x;
	_y += point._y;

	return (*this);
}


Point &Point::operator-=(const Point &point)
{
	_x = point._x;
	_y = point._y;

	return (*this);
}


int Point::operator[](int i) const
{
	return ((i % 2)
			? get_y()
			: get_x());
}


int Point::operator[](char axis) const
{
	if (axis == 'x')
		return get_x();

	if (axis == 'y')
		return get_y();

	return 0;
}


std::ostream &operator<<(std::ostream &out, const Point &point)
{
	return out << "[" << point._x << ", " << point._y << "]";
}


std::istream &operator>>(std::istream &in, Point &point)
{
	char c;
	in >> c >> point._x >> c >> c >> point._y >> c;
	return in;
}
