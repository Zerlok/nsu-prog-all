#ifndef __SCREW_SHADER_HPP__
#define __SCREW_SHADER_HPP__


#include "core/shader.hpp"


class ScrewShader : public Shader
{
	public:
		ScrewShader();
		~ScrewShader();

		void passObject(const Object*) const;

		void _registerAttributes() override;
		void _passInternalAttributes() override;

		void passComponent(const Component*) const override;
		void passArrayOfComponents(const ComponentsPtrs&) const override;

	private:
		static const std::string VS_FILE;

		GLuint _attrAlpha;
};


#endif // __SCREW_SHADER_HPP__
