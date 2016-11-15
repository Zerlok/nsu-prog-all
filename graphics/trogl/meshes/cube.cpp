#include "cube.hpp"


#include "core/material.hpp"
#include "materials/diffusematerial.hpp"


Cube::Cube(const float& radius,
		   const size_t& subdivideLevel)
	: Mesh("Cube")
{
	addVertex(-radius, -radius, -radius);
	addVertex(-radius, +radius, -radius);
	addVertex(+radius, +radius, -radius);
	addVertex(+radius, -radius, -radius);

	addVertex(-radius, -radius, +radius);
	addVertex(-radius, +radius, +radius);
	addVertex(+radius, +radius, +radius);
	addVertex(+radius, -radius, +radius);

	addPolygon(0, 1, 2);
	addPolygon(0, 2, 3);
	addPolygon(5, 7, 6);
	addPolygon(5, 4, 7);
	addPolygon(1, 4, 5);
	addPolygon(1, 0, 4);
	addPolygon(2, 1, 5);
	addPolygon(2, 5, 6);
	addPolygon(3, 2, 6);
	addPolygon(3, 6, 7);
	addPolygon(0, 4, 7);
	addPolygon(0, 7, 3);
}


Cube::~Cube()
{
}
