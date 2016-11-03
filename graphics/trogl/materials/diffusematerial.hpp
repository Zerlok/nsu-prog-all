#ifndef __DIFFUSE_MATERIAL_HPP__
#define __DIFFUSE_MATERIAL_HPP__


#include "core/material.hpp"


class DiffuseMaterial : public Material
{
	public:
		DiffuseMaterial(const Color& color = Material::DEFAULT_COLOR);
		~DiffuseMaterial();
};


#endif // __DIFFUSE_MATERIAL_HPP__
