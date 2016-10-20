#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__


#include <sharedpointer.h>
#include "component.hpp"
#include "shader.hpp"


class Material : public Component
{
	public:
		Material(const std::string& name = "",
				 const ShaderPtr& vertexShader = DEFAULT_VERTEX_SHADER,
				 const ShaderPtr& fragmentShader = DEFAULT_FRAGMENT_SHADER);
		Material(const Material& mat);
		Material(Material&& mat);
		virtual ~Material();

		Material& operator=(const Material& mat);
		Material& operator=(Material&& mat);

		const ShaderPtr& getVertexShader() const;
		const ShaderPtr& getFragmentShader() const;

		void setVertexShader(const ShaderPtr& vertexShader);
		void setFragmentShader(const ShaderPtr& fragmentShader);

	protected:
		static const ShaderPtr DEFAULT_VERTEX_SHADER;
		static const ShaderPtr DEFAULT_FRAGMENT_SHADER;

		// TODO: add light behavior (is it in shaders?).
		ShaderPtr _vertexShader;
		ShaderPtr _fragmentShader;
};

using MaterialPtr = SharedPointer<Material>;


#endif // __MATERIAL_HPP__
