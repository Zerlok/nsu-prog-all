#include "cube.hpp"


#include "material.hpp"
#include "materials/diffusematerial.hpp"


Cube::Cube(const float& radius,
		   const Color& color,
		   const size_t& subdivideLevel)
	: Mesh("Cube")
{
	addVertex(-radius, -radius, -radius, color);
	addVertex(-radius, +radius, -radius, color);
	addVertex(+radius, +radius, -radius, color);
	addVertex(+radius, -radius, -radius, color);

	addVertex(-radius, -radius, +radius, color);
	addVertex(-radius, +radius, +radius, color);
	addVertex(+radius, +radius, +radius, color);
	addVertex(+radius, -radius, +radius, color);

	addFace(0, 2, 1);
	addFace(0, 3, 2);
	addFace(5, 6, 7);
	addFace(5, 7, 4);
	addFace(1, 5, 4);
	addFace(1, 4, 0);
	addFace(2, 5, 1);
	addFace(2, 6, 5);
	addFace(3, 6, 2);
	addFace(3, 7, 6);
	addFace(0, 7, 4);
	addFace(0, 3, 7);
}


Cube::~Cube()
{
}
