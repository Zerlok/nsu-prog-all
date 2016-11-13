#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__


#include "core/mesh.hpp"


class Sphere : public Mesh
{
	public:
		Sphere(const float& radius = 1.0,
			   const size_t& rowsNum = 0,
			   const size_t& segmentsNum = 0);
		~Sphere();
};

#endif // __SPHERE_HPP__
