#include "cube.hpp"


#include "core/material.hpp"
#include "materials/diffusematerial.hpp"


Cube::Cube(const float& radius,
		   const Color& color,
		   const size_t& subdivideLevel)
	: Mesh("Cube", Mesh::DEFAULT_MATERIAL)
{
	addVertex(-radius, -radius, -radius, color);
	addVertex(-radius, +radius, -radius, color);
	addVertex(+radius, +radius, -radius, color);
	addVertex(+radius, -radius, -radius, color);

	addVertex(-radius, -radius, +radius, color);
	addVertex(-radius, +radius, +radius, color);
	addVertex(+radius, +radius, +radius, color);
	addVertex(+radius, -radius, +radius, color);

	addFace(0, 1, 2);
	addFace(0, 2, 3);
	addFace(5, 7, 6);
	addFace(5, 4, 7);
	addFace(1, 4, 5);
	addFace(1, 0, 4);
	addFace(2, 1, 5);
	addFace(2, 5, 6);
	addFace(3, 2, 6);
	addFace(3, 6, 7);
	addFace(0, 4, 7);
	addFace(0, 7, 3);
}


Cube::~Cube()
{
}
