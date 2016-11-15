#include "plane.hpp"


Plane::Plane()
	: Mesh("Plane")
{
	addVertex(1.0, 0.1, 1.0);
	addVertex(1.0, 0.1, -1.0);
	addVertex(-1.0, 0.1, 1.0);
	addVertex(-1.0, 0.1, -1.0);

	addPolygon(0, 1, 2);
	addPolygon(1, 3, 2);
}


Plane::~Plane()
{
}

