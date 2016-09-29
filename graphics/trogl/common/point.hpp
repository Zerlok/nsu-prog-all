#ifndef __POINT_HPP__
#define __POINT_HPP__


class Point
{
	public:
		static const Point zero;

		Point(const int& x, const int& y, const int& z);
		Point(const Point& p);
		Point(Point&& p);
		~Point();

		Point& operator=(const Point& p);
		Point& operator=(Point&& p);

		bool operator==(const Point& p) const;
		bool operator!=(const Point& p) const;

		double distance(const Point& p) const;

	private:
		int _x;
		int _y;
		int _z;
};


#endif // __POINT_HPP__
