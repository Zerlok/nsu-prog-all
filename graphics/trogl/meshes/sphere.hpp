#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__


#include "mesh.hpp"


class Sphere : public Mesh
{
	public:
		Sphere(const float& radius = 1.0,
			   const size_t& rows = 16,
			   const size_t& segments = 32);
		~Sphere();
};

#endif // __SPHERE_HPP__
