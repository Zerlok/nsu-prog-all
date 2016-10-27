#ifndef __DIFFUSE_SHADER_HPP__
#define __DIFFUSE_SHADER_HPP__


#include <string>
#include "shader.hpp"


class DiffuseShader : public Shader
{
	public:
		DiffuseShader();
		~DiffuseShader();

		void initCustomVarsLocations() override;
		void prepareForRender() override;

	private:
		static const std::string VS_FILE;
		static const std::string FS_FILE;
};


#endif // __DIFFUSE_SHADER_HPP__
