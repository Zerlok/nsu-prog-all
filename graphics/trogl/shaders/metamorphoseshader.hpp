#ifndef __METAMORPHOSE_SHADER_HPP__
#define __METAMORPHOSE_SHADER_HPP__


#include <string>
#include "opengls.hpp"
#include "shader.hpp"


class MetamorphoseShader : public Shader
{
	public:
		MetamorphoseShader();
		~MetamorphoseShader();

		void initCustomVarsLocations(const GLuint &glShaderProgram);
		void prepareForRender();

	private:
		static const std::string SRC;

		GLuint _attrCosSqAlpha;
};


#endif // __METAMORPHOSE_SHADER_HPP__
