#include "cube.hpp"


Cube::Cube(const float& r, const Color& c)
	: Mesh()
{
	addVertex(Vertex(-r, -r, -r, c));
	addVertex(Vertex(-r, +r, -r, c));
	addVertex(Vertex(+r, +r, -r, c));
	addVertex(Vertex(+r, -r, -r, c));

	addVertex(Vertex(-r, -r, +r, c));
	addVertex(Vertex(-r, +r, +r, c));
	addVertex(Vertex(+r, +r, +r, c));
	addVertex(Vertex(+r, -r, +r, c));

	addFace(Face(0, 2, 1));
	addFace(Face(0, 3, 2));
	addFace(Face(5, 6, 7));
	addFace(Face(5, 7, 4));
	addFace(Face(1, 5, 4));
	addFace(Face(1, 4, 0));
	addFace(Face(2, 5, 1));
	addFace(Face(2, 6, 5));
	addFace(Face(3, 6, 2));
	addFace(Face(3, 7, 6));
	addFace(Face(0, 7, 4));
	addFace(Face(0, 3, 7));
}


Cube::~Cube()
{
}
