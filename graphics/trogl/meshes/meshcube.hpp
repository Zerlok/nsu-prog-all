#ifndef __MESHCUBE_HPP__
#define __MESHCUBE_HPP__


#include "mesh.hpp"


class MeshCube : public Mesh
{
	public:
		MeshCube(const Point& pos = Point::zero,
				 const Point& rot = Point::zero,
				 const Point& sca = Point::one,
				 const Color& mainColor = Color::white,
				 const Color& bordersColor = Color::black);
		~MeshCube();
};

#endif // __MESHCUBE_HPP__
