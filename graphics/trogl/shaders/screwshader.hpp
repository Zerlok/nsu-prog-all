#ifndef __SCREW_SHADER_HPP__
#define __SCREW_SHADER_HPP__


#include "core/shader.hpp"


class ScrewShader : public Shader
{
	public:
		ScrewShader();
		~ScrewShader();

		void registerInternalAttributes() override;
		void passInternalAttributes() override;
		void passObject(Object const*) override;

	private:
		static const std::string VS_FILE;

		GLuint _attrAlpha;
};


#endif // __SCREW_SHADER_HPP__
