#ifndef __MESHCUBE_HPP__
#define __MESHCUBE_HPP__


#include "mesh.hpp"


class StrangeCube : public Mesh
{
	public:
		StrangeCube(const Color& borderColor = Color::white,
					const Color& innerColor = Color::black);
		~StrangeCube();
};

#endif // __MESHCUBE_HPP__
