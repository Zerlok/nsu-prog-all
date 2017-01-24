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

		// Static methods.
		static Light createPoint();
		static Light createSun();
		static Light createSpot();

		// Constructors / Destructor.
		Light(const Type& type,
			  const std::string& name = "");
		Light(const Light& light);
		Light(Light&& light);
		~Light();

		// Operators.
		Light& operator=(const Light& light);
		Light& operator=(Light&& light);

		Light& operator+=(const Light& light);
		Light& operator*=(const float& ratio);
		Light operator+(const Light& light) const;
		Light operator*(const float& ratio) const;

		// Methods.
		const Type& getLightType() const;
		const float& getPower() const;
		const vec3& getDirection() const;
		const Color& getColor() const;
		const float& getInnerAngle() const;
		const float& getOutterAngle() const;

		const glm::mat4x4& getViewMatrix() const;
		const glm::mat4x4& getProjMatrix() const;

		ShaderPtr& getShader();
		const ShaderPtr& getShader() const;

		void setPower(const float& power);
		void setDirection(const vec3& direction);
		void setColor(const Color& color);
		void setInnerAngle(const float& innerAngle);
		void setOutterAngle(const float& outterAngle);
		void setShader(const ShaderPtr& sh);

		void faceDirectionTo(const vec3& position);

		// Overriden methods.
		void setPosition(const vec3 &position) override;

		void applyPosition() override;
		void applyRotation() override;
		void applyScale() override;

	protected:
		void _regProperties() override;

	private:
		// Static methods.
		static bool _hasDirection(const Type& type);
		static bool _hasAngles(const Type& type);

		// Fields.
		Type _lightType;
		float _power;
		vec3 _direction;
		Color _color;
		float _innerAngle;
		float _outterAngle;

		glm::mat4x4 _viewMat;
		glm::mat4x4 _projMat;

		ShaderPtr _shader;
};

std::ostream& operator<<(std::ostream& out, const Light::Type& type);

using LightPtr = SharedPointer<Light, Object>;
using Lights = std::list<LightPtr>;


#endif // __LIGHT_HPP__
