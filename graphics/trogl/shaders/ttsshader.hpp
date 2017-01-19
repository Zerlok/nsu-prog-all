#ifndef __TTS_SHADER_HPP__
#define __TTS_SHADER_HPP__


#include "core/shader.hpp"


class TTSShader : public Shader
{
	public:
		TTSShader();
		~TTSShader();

		void passComponent(const Component*) const override;
		void passTextures(const Textures &) const override;

	protected:
		void _registerUniforms() override;
		void _passInternalUniforms() override;
};


#endif // __TTS_SHADER_HPP__
