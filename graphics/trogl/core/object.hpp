#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__


#include <string>
#include <glm/glm.hpp>
#include <sharedpointer.h>
#include "component.hpp"


namespace space
{
	namespace zero
	{
		static const glm::vec2 xy(0.0f, 0.0f);
		static const glm::vec3 xyz(0.0f, 0.0f, 0.0f);

		static const glm::mat4x4 m3x3(0);
		static const glm::mat4x4 m4x4(0);
	}

	namespace identic
	{
		static const glm::mat4x4 m3x3(1);
		static const glm::mat4x4 m4x4(1);
	}

	namespace axis
	{
		static const glm::vec3 x(1.0f, 0.0f, 0.0f);
		static const glm::vec3 y(0.0f, 1.0f, 0.0f);
		static const glm::vec3 z(0.0f, 0.0f, 1.0f);
	}
}


using vec2 = glm::vec2;
using vec3 = glm::vec3;


class Object : public Component
{
	public:
		// Inner classes.
		enum class Type
		{
			MESH = 'M',
			LIGHT = 'L',
			CAMERA = 'C',
		};

		// Constructors / Destructor.
		Object(const Type& type,
			   const std::string& name = DEFAULT_NAME);
		Object(const Object& obj);
		Object(Object&& obj);
		virtual ~Object();

		// Operators.
		Object& operator=(const Object& obj);
		Object& operator=(Object&& obj);

		Object& operator+=(const Object& obj);
		Object& operator*=(const float& ratio);
		Object operator+(const Object& obj) const;
		Object operator*(const float& ratio) const;

		// Methods.
		const Type& getObjectType() const;

		const vec3& getPosition() const;
		const vec3& getRotation() const;
		const vec3& getScale() const;

		Object& toObject();
		const Object& toObject() const;

		void setPosition(const float& x,
						 const float& y,
						 const float& z);
		void setRotation(const float& x,
						 const float& y,
						 const float& z);
		void setScale(const float& x,
					  const float& y,
					  const float& z);

		// Virtual methods.
		virtual void setPosition(const vec3& position);
		virtual void setRotation(const vec3& rotation);
		virtual void setScale(const vec3& scale);

		virtual void applyPosition();
		virtual void applyRotation();
		virtual void applyScale();

		// Friend functions.
		friend std::ostream& operator<<(std::ostream& out, const Object& obj);

	private:
		Type _objectType;

	protected:
		// Static fields.
		static const std::string DEFAULT_NAME;
		static const vec3 DEFAULT_POSITION;
		static const vec3 DEFAULT_ROTATION;
		static const vec3 DEFAULT_SCALE;

		// Fields.
		vec3 _position;
		vec3 _rotation;
		vec3 _scale;

		// Methods.
		virtual void _regProperties() override;

	private:
		// Static fields.
		static size_t _meshID;
		static size_t _lightID;
		static size_t _cameraID;

		// Static methods.
		static std::string _generateNameFromObjType(const Type& type);
};

using ObjectPtr = SharedPointer<Object, Component>;


std::ostream& operator<<(std::ostream& out, const Object& obj);
std::ostream& operator<<(std::ostream& out, const vec2& v);
std::ostream& operator<<(std::ostream& out, const vec3& v);



#endif // __OBJECT_HPP__
