#ifndef __SCREW_SHADER_HPP__
#define __SCREW_SHADER_HPP__


#include "../shader.hpp"


class ScrewShader : public Shader
{
	public:
		ScrewShader();
		~ScrewShader();

		void initCustomVarsLocations(const GLuint &glShaderProgram);
		void prepareForRender();

	private:
		static const std::string SRC;

		GLuint _attrAlpha;
};


#endif // __SCREW_SHADER_HPP__
