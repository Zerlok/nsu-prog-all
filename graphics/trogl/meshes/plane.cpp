#include "plane.hpp"


Plane::Plane()
	: Mesh("Plane")
{
	addVertex(0.5, 0.0, 0.5, 0.0, 1.0, 0.0, 1.0, 0.0);
	addVertex(0.5, 0.0, -0.5, 0.0, 1.0, 0.0, 1.0, 1.0);
	addVertex(-0.5, 0.0, 0.5, 0.0, 1.0, 0.0, 0.0, 0.0);
	addVertex(-0.5, 0.0, -0.5, 0.0, 1.0, 0.0, 0.0, 1.0);

	addPolygon(0, 1, 2);
	addPolygon(1, 3, 2);
}


Plane::~Plane()
{
}

