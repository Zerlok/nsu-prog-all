#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__


#include <list>
#include <sharedpointer.h>
#include "common/color.hpp"
#include "shader.hpp"
#include "object.hpp"


class Light : public Object
{
	public:
		// Inner classes.
		enum class Type
		{
			// Do not change these values - harcoded in shaders.
			POINT = 1,
			SUN = 2,
			SPOT = 3,
			AMBIENT = 4,
		};

		// Constructors / Destructor.
		Light(const Type& type);
		Light(const Light& light);
		Light(Light&& light);
		~Light();

		// Operators.
		Light& operator=(const Light& light);
		Light& operator=(Light&& light);

		// Methods.
		const Type& getLightType() const;
		const float& getPower() const;
		const glm::vec3& getDirection() const;
		const Color& getColor() const;
		const float& getInnerAngle() const;
		const float& getOutterAngle() const;

		void setPower(const float& power);
		void setDirection(const glm::vec3& direction);
		void setColor(const Color& color);
		void setInnerAngle(const float& innerAngle);
		void setOutterAngle(const float& outterAngle);

		// Overriden methods.
		void applyPosition() override;
		void applyRotation() override;
		void applyScale() override;

	private:
		// Static methods.
		static bool _hasDirection(const Type& type);
		static bool _hasAngles(const Type& type);

		// Fields.
		Type _lightType;
		float _power;
		glm::vec3 _direction;
		Color _color;
		float _innerAngle;
		float _outterAngle;
};

std::ostream& operator<<(std::ostream& out, const Light::Type& type);

using LightPtr = SharedPointer<Light>;
using Lights = std::list<LightPtr>;


#endif // __LIGHT_HPP__
