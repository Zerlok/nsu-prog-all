#ifndef __METAMORPHOSE_SHADER_HPP__
#define __METAMORPHOSE_SHADER_HPP__


#include <string>
#include "core/shader.hpp"


class MetamorphoseShader : public Shader
{
	public:
		MetamorphoseShader();
		~MetamorphoseShader();

		void _registerAttributes() override;
		void _passInternalAttributes() override;
		void passObject(Object const*obj) override;

	private:
		static const std::string VS_FILE;

		GLuint _attrObjPosition;
		GLuint _attrCosSqAlpha;
};


#endif // __METAMORPHOSE_SHADER_HPP__
