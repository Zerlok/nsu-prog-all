#ifndef __CYLINDER_HPP__
#define __CYLINDER_HPP__


#include "common/color.hpp"
#include "core/mesh.hpp"


class Cylinder : public Mesh
{
	public:
		Cylinder(const size_t& segments = 16,
				 const size_t& rows = 0);
		~Cylinder() {}
};


#endif // __CYLINDER_HPP__
