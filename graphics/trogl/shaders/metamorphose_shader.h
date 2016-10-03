#ifndef __METAMORPHOSE_SHADER_HPP__
#define __METAMORPHOSE_SHADER_HPP__


#include "../shader.hpp"
#include "common/utils.h"


class MetamorphoseShader : public Shader
{
	public:
		MetamorphoseShader();
		~MetamorphoseShader();

	private:
		static const std::string SRC;
};


#endif // __METAMORPHOSE_SHADER_HPP__
