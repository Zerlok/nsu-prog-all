#ifndef __DIFFUSE_SHADER_HPP__
#define __DIFFUSE_SHADER_HPP__


#include <string>
#include "core/component.hpp"
#include "core/object.hpp"
#include "core/mesh.hpp"
#include "core/light.hpp"
#include "core/camera.hpp"
#include "core/shader.hpp"


class DiffuseShader : public Shader
{
	public:
		// Constructors / Destructor.
		DiffuseShader();
		~DiffuseShader();

		// Methods.
		void passObject(const Object* obj) const;
		void passCamera(const Camera* camera) const;
		void passLight(const Light* light) const;

		// Overriden methods.
		void passComponent(const Component* comp) const override;
		void passTextures(const Textures& textures) const override;

	protected:
		void _registerUniforms() override;
		void _passInternalUniforms() override;
};


#endif // __DIFFUSE_SHADER_HPP__
