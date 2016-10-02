#ifndef __MESH_CUBE_HPP__
#define __MESH_CUBE_HPP__


#include "../mesh.hpp"


class Cube : public Mesh
{
	public:
		Cube(const float& r,
			 const Color& c = Color::grey);
		~Cube();
};


#endif // __MESH_CUBE_HPP__
