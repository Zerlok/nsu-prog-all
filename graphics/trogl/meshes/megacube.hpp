#ifndef __MEGACUBE_HPP__
#define __MEGACUBE_HPP__


#include "common/color.hpp"
#include "core/mesh.hpp"


class MegaCube : public Mesh
{
	public:
		MegaCube(const Color& c1, const Color& c2);
		~MegaCube();
};


#endif // __MEGACUBE_HPP__
