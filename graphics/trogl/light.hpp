#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__


#include <sharedpointer.h>
#include "shader.hpp"
#include "object.hpp"


class Light : public Object
{
	public:
		// Inner classes.
		enum class Type
		{
			POINT = 0,
			DIRCTIONAL = 1,
			SPOT = 2,
		};

		// Constructors / Destructor.
		Light(const Type& type,
			  const ShaderPtr& shader);
		Light(const Light& light);
		Light(Light&& light);
		~Light();

		// Operators.
		Light& operator=(const Light& light);
		Light& operator=(Light&& light);

		// Methods.
		const Type& getLightType() const;
		const ShaderPtr& getShader() const;

		void setShader(const ShaderPtr& shader);

	protected:
		// Fields.
		Type _lightType;
		ShaderPtr _shader;
};

using LightPtr = SharedPointer<Light>;


#endif // __LIGHT_HPP__
