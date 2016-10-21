#ifndef __CYLINDER_HPP__
#define __CYLINDER_HPP__


#include "common/color.hpp"
#include "mesh.hpp"


class Cylinder : public Mesh
{
	public:
		Cylinder(const Color& c1, const Color& c2);
		~Cylinder();
};


#endif // __CYLINDER_HPP__
