#ifndef __ICOSPHERE_HPP__
#define __ICOSPHERE_HPP__


#include <vector>
#include "core/mesh.hpp"


class Icosphere : public Mesh
{
	public:
		static const float X;
		static const float Y;
		static const float Z;
		static const std::vector<vec3> baseVertices;
		static const std::vector<Triple> basePolygons;

		Icosphere(const float& radius = 1.0,
				  const size_t& subdivide = 0);
		~Icosphere();
};


#endif // __ICOSPHERE_HPP__
