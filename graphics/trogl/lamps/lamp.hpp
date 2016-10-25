#ifndef __LAMP_HPP__
#define __LAMP_HPP__


#include "shader.hpp"
#include "shaders/diffuseshader.hpp"
#include "light.hpp"


class Lamp : public Light
{
	public:
		static const DiffuseShader DIFFUSE_SHADER;

		Lamp();
		~Lamp();
};


#endif // __LAMP_HPP__
