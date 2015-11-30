#ifndef __POINT_H__
#define __POINT_H__


#include <iostream>


class Point
{
	public:
		static const Point zero;

		Point(int x=0, int y=0);
		Point(int coordinates[2]);
		Point(const Point &point);
		Point(Point &&point);
		virtual ~Point();

		int get_x() const;
		int get_y() const;

		double distance_to(const Point &point) const;

		Point &operator=(const Point &point);

		bool operator==(const Point &point) const;
		bool operator!=(const Point &point) const;
		bool operator==(int coordinates[2]) const;
		bool operator!=(int coordinates[2]) const;

		bool operator<(const Point &point) const;
		bool operator>(const Point &point) const;
		bool operator<(int coordinates[2]) const;
		bool operator>(int coordinates[2]) const;

		bool operator<=(const Point &point) const;
		bool operator>=(const Point &point) const;
		bool operator<=(int coordinates[2]) const;
		bool operator>=(int coordinates[2]) const;

		Point operator+(const Point &point) const;
		Point operator-(const Point &point) const;

		Point &operator+=(const Point &point);
		Point &operator-=(const Point &point);

		int operator[](int i) const;
		int operator[](char axis) const;

		friend std::ostream &operator<<(std::ostream &out, const Point &point);

	private:
		int _x;
		int _y;
};

std::ostream &operator<<(std::ostream &out, const Point &point);


// __POINT_H__
#endif
