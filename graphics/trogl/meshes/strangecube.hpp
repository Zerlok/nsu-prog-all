#ifndef __MESHCUBE_HPP__
#define __MESHCUBE_HPP__


#include "common/color.hpp"
#include "mesh.hpp"


class StrangeCube : public Mesh
{
	public:
		StrangeCube(const Color& c1 = Color::white,
					const Color& c2 = Color::black);
		~StrangeCube();
};


#endif // __MESHCUBE_HPP__
