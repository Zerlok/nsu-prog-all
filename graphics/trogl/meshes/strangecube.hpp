#ifndef __MESHCUBE_HPP__
#define __MESHCUBE_HPP__


#include "mesh.hpp"


class StrangeCube : public Mesh
{
	public:
		StrangeCube(const Point& pos = Point::zero,
					const Point& rot = Point::zero,
					const Point& sca = Point::one,
					const Color& mainColor = Color::white,
					const Color& bordersColor = Color::black);
		~StrangeCube();
};

#endif // __MESHCUBE_HPP__
