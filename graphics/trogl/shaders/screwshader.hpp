#ifndef __SCREW_SHADER_HPP__
#define __SCREW_SHADER_HPP__


#include "../shader.hpp"


class ScrewShader : public Shader
{
	public:
		ScrewShader();
		~ScrewShader();

	private:
		static const std::string SRC;
};


#endif // __SCREW_SHADER_HPP__
