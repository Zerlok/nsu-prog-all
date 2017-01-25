#ifndef __MESH_CUBE_HPP__
#define __MESH_CUBE_HPP__


#include "common/color.hpp"
#include "core/mesh.hpp"


class Cube : public Mesh
{
	public:
		Cube(const float& radius = 1.0,
			 const size_t& subdivideLevel = 0);
		~Cube();
};


#endif // __MESH_CUBE_HPP__
