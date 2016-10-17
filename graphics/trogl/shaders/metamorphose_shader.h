#ifndef __METAMORPHOSE_SHADER_HPP__
#define __METAMORPHOSE_SHADER_HPP__


#include "../shader.hpp"


class MetamorphoseShader : public Shader
{
	public:
		MetamorphoseShader();
		~MetamorphoseShader();

		void initUniformsLocations(const GLuint &glShaderProgram);
		void prepareForRender();

	private:
		static const std::string SRC;

		GLuint _attrCosSqAlpha;
};


#endif // __METAMORPHOSE_SHADER_HPP__