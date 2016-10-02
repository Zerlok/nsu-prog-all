#ifndef __POINT_HPP__
#define __POINT_HPP__


class Point
{
	public:
		static const Point zero;
		static const Point one;

		Point(const float& x = 0, const float& y = 0, const float& z = 0);
		Point(const Point& p);
		Point(Point&& p);
		~Point();

		Point& operator=(const Point& p);
		Point& operator=(Point&& p);

		bool operator==(const Point& p) const;
		bool operator!=(const Point& p) const;

		Point& operator+=(const Point& p);
		Point operator+(const Point& p) const;

		Point& operator-=(const Point& p);
		Point operator-(const Point& p) const;

		double distance(const Point& p) const;
		Point crossProduct(const Point& p) const;
		double dotProduct(const Point& p) const;

		const float& getX() const;
		const float& getY() const;
		const float& getZ() const;

	private:
		float _x;
		float _y;
		float _z;
};


#endif // __POINT_HPP__
