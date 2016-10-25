#ifndef __DIFFUSE_SHADER_HPP__
#define __DIFFUSE_SHADER_HPP__


#include <string>
#include "shader.hpp"


class DiffuseShader : public Shader
{
	public:
		DiffuseShader();
		~DiffuseShader();

		void initCustomVarsLocations(const GLuint &glProgram) override;
		void prepareForRender() override;

	private:
		static const std::string SRC;
};


#endif // __DIFFUSE_SHADER_HPP__
