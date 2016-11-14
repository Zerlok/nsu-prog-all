#ifndef __DIFFUSE_MATERIAL_HPP__
#define __DIFFUSE_MATERIAL_HPP__


#include "core/material.hpp"


class DiffuseMaterial : public Material
{
	public:
		// Constructors / Destructor.
		DiffuseMaterial(const Color& color = Material::DEFAULT_COLOR);
		~DiffuseMaterial();

		// Methods.
		const float& getDiffuse() const;
		const float& getSpecular() const;

		void setDiffuse(const float& diffuse);
		void setSpecular(const float& specular);

		// Overriden methods.
		void passToShader() override;

	private:
		float _diffuse;
		float _specular;
};


#endif // __DIFFUSE_MATERIAL_HPP__
