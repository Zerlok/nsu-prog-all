#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__


#include <string>
#include <sharedpointer.h>
#include "opengls.hpp"
#include "animation.hpp"


using vec2 = glm::vec2;
using vec3 = glm::vec3;
using vec4 = glm::vec4;


class Object : public Animatable
{
	public:
		// Constructors / Destructor.
		Object(const Type& type,
			   const std::string& name = DEFAULT_NAME);
		Object(const Object& obj);
		Object(Object&& obj);
		virtual ~Object();

		// Operators.
		Object& operator=(const Object& obj);
		Object& operator=(Object&& obj);

		// Methods.
		const vec3& getPosition() const;
		const vec3& getRotation() const;
		const vec3& getScale() const;

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
};

using ObjectPtr = SharedPointer<Object, Animatable>;


std::ostream& operator<<(std::ostream& out, const Object& obj);


#endif // __OBJECT_HPP__
