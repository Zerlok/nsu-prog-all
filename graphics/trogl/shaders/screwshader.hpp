#ifndef __SCREW_SHADER_HPP__
#define __SCREW_SHADER_HPP__


#include "../shader.hpp"


class ScrewShader : public Shader
{
	public:
		ScrewShader();
		~ScrewShader();

		void initCustomVarsLocations() override;
		void prepareForRender() override;

	private:
		static const std::string VS_FILE;

		GLuint _attrAlpha;
};


#endif // __SCREW_SHADER_HPP__
