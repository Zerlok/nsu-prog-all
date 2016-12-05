#include "icosphere.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLDebug, loggerDFull);


const float Icosphere::X = 0.525731112119133606f;
const float Icosphere::Y = 0.0f;
const float Icosphere::Z = 0.850650808352039932f;
const std::vector<Object::vec> Icosphere::baseVertices = {
	{-X, +Y, +Z},
	{+X, +Y, +Z},
	{-X, +Y, -Z},
	{+X, +Y, -Z},
	{+Y, +Z, +X},
	{+Y, +Z, -X},
	{+Y, -Z, +X},
	{+Y, -Z, -X},
	{+Z, +X, +Y},
	{-Z, +X, +Y},
	{+Z, -X, +Y},
	{-Z, -X, +Y}
};
const std::vector<Mesh::Triple> Icosphere::basePolygons = {
	{0,4,1},{0,9,4},{9,5,4},{4,5,8},{4,8,1},
	{8,10,1},{8,3,10},{5,3,8},{5,2,3},{2,7,3},
	{7,10,3},{7,6,10},{7,11,6},{11,0,6},{0,1,6},
	{6,1,10},{9,0,11},{9,11,2},{9,2,5},{7,2,11}
};


Icosphere::Icosphere(const float& radius,
					 const size_t& subdivide)
{
	// TODO: add subdivision (https://schneide.wordpress.com/2016/07/15/generating-an-icosphere-in-c/).
	for (vec coords : baseVertices)
	{
		coords *= radius;
		addVertex(coords.x, coords.y, coords.z);
	}

	for (const Triple& tr : basePolygons)
		addPolygon(tr.getFirst(), tr.getSecond(), tr.getThird());
}


Icosphere::~Icosphere()
{
}

