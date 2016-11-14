#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__


#include <sharedpointer.h>
#include "common/color.hpp"
#include "shader.hpp"
#include "component.hpp"


class Material : public Component
{
	public:
		// Constructors / Destructor.
		Material(const std::string& name = "",
				 const Color& color = DEFAULT_COLOR,
				 const ShaderPtr& shader = DEFAULT_SHADER);
		Material(const Material& mat);
		Material(Material&& mat);
		virtual ~Material();

		// Operators.
		Material& operator=(const Material& mat);
		Material& operator=(Material&& mat);

		// Methods.
		const Color& getColor() const;
		const ShaderPtr& getShader() const;

		void setColor(const Color& color);
		void setShader(const ShaderPtr& shader);

		// Virtual methods.
		virtual void passToShader() {}

	protected:
		// Static fields.
		static const Color DEFAULT_COLOR;
		static const ShaderPtr DEFAULT_SHADER;

		// Fields.
		Color _color;
		ShaderPtr _shader;
};

using MaterialPtr = SharedPointer<Material>;


#endif // __MATERIAL_HPP__
