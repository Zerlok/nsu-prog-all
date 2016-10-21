#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__


#include <sharedpointer.h>
#include "shader.hpp"
#include "component.hpp"


class Material : public Component
{
	public:
		Material(const std::string& name = "",
				 const ShaderPtr& shader = DEFAULT_SHADER);
		Material(const Material& mat);
		Material(Material&& mat);
		virtual ~Material();

		Material& operator=(const Material& mat);
		Material& operator=(Material&& mat);

		const ShaderPtr& getShader() const;
		void setShader(const ShaderPtr& shader);

	protected:
		static const ShaderPtr DEFAULT_SHADER;

		ShaderPtr _shader;
};

using MaterialPtr = SharedPointer<Material>;


#endif // __MATERIAL_HPP__
