#ifndef __LIGHT_SHADER_HPP__
#define __LIGHT_SHADER_HPP__


#include <string>
#include "core/component.hpp"
#include "core/light.hpp"
#include "core/shader.hpp"


class LightShader : public Shader
{
	public:
		LightShader();
		~LightShader();

		void passLight(const Light* light) const;

		void passComponent(const Component* comp) const override;
		void passTextures(const Textures& textures) const override;

	protected:
		void _registerUniforms() override;
		void _passInternalUniforms() override;
};


#endif // __LIGHT_SHADER_HPP__
