#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__


#include <sharedpointer.h>
#include "component.hpp"
#include "shader.hpp"


class Material : public Component
{
	public:
		Material(const std::string& name = "",
				 const ShaderPtr& shader = nullptr);
		Material(const Material& mat);
		Material(Material&& mat);
		virtual ~Material();

		Material& operator=(const Material& mat);
		Material& operator=(Material&& mat);

	protected:
		// TODO: add light behavior.
		ShaderPtr _shader;
};

using MaterialPtr = SharedPointer<Material>;


#endif // __MATERIAL_HPP__
