#ifndef __PLANE_HPP__
#define __PLANE_HPP__


#include "common/color.hpp"
#include "core/mesh.hpp"


class Plane : public Mesh
{
	public:
		Plane(const Color& color = Color::white);
		~Plane();
};


#endif // __PLANE_HPP__
