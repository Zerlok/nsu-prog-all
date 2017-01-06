#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__


#include <string>
#include <glm/glm.hpp>
#include <sharedpointer.h>
#include "component.hpp"


namespace zero
{
	static const glm::vec2 xy(0.0f, 0.0f);
	static const glm::vec3 xyz(0.0f, 0.0f, 0.0f);
}


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

		using vec = glm::vec3;

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
		const Type& getObjectType() const;

		const vec& getPosition() const;
		const vec& getRotation() const;
		const vec& getScale() const;

		Object& toObject();
		const Object& toObject() const;

		// Virtual methods.
		virtual void setPosition(const vec& position);
		virtual void setRotation(const vec& rotation);
		virtual void setScale(const vec& scale);

		virtual void applyPosition() = 0;
		virtual void applyRotation() = 0;
		virtual void applyScale() = 0;

		// Friend functions.
		friend std::ostream& operator<<(std::ostream& out, const Object& obj);

	private:
		Type _objectType;

	protected:
		// Static fields.
		static const std::string DEFAULT_NAME;
		static const vec DEFAULT_POSITION;
		static const vec DEFAULT_ROTATION;
		static const vec DEFAULT_SCALE;
		static const vec AXIS_X;
		static const vec AXIS_Y;
		static const vec AXIS_Z;

		// Fields.
		vec _position;
		vec _rotation;
		vec _scale;

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

std::ostream& operator<<(std::ostream& out, const Object::vec& v);



#endif // __OBJECT_HPP__
