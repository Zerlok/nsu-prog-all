#include "plane.hpp"


Plane::Plane(const Color& color)
	: Mesh("Plane")
{
	addVertex(1.0, 0.1, 1.0, color);
	addVertex(1.0, 0.1, -1.0, color);
	addVertex(-1.0, 0.1, 1.0, color);
	addVertex(-1.0, 0.1, -1.0, color);

	addPolygon(0, 1, 2);
	addPolygon(1, 3, 2);
}


Plane::~Plane()
{
}

