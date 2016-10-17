#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__


#include "component.hpp"
#include "shader.hpp"


class Material : public Component
{
	public:
		Material(const std::string& name = std::string(),
				 const Shader& shader = Shader());
		Material(const Material& mat);
		Material(Material&& mat);
		virtual ~Material();

		Material& operator=(const Material& mat);
		Material& operator=(Material&& mat);

	protected:
		// TODO: add light behavior.
		Shader _shader;
};


#endif // __MATERIAL_HPP__
