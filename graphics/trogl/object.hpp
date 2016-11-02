#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__


#include <string>
#include <glm/glm.hpp>
#include <sharedpointer.h>
#include "component.hpp"


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

		// Methods.
		const Type& getObjectType() const;

		const glm::vec3& getPosition() const;
		const glm::vec3& getRotation() const;
		const glm::vec3& getScale() const;

		// Virtual methods.
		virtual void setPosition(const glm::vec3& position);
		virtual void setRotation(const glm::vec3& rotation);
		virtual void setScale(const glm::vec3& scale);

		virtual void applyPosition() = 0;
		virtual void applyRotation() = 0;
		virtual void applyScale() = 0;

	private:
		Type _object_type;

	protected:
		// Static fields.
		static const std::string DEFAULT_NAME;
		static const glm::vec3 DEFAULT_POSITION;
		static const glm::vec3 DEFAULT_ROTATION;
		static const glm::vec3 DEFAULT_SCALE;
		static const glm::vec3 AXIS_X;
		static const glm::vec3 AXIS_Y;
		static const glm::vec3 AXIS_Z;

		// Fields.
		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;

	private:
		// Static fields.
		static size_t _meshID;
		static size_t _lightID;
		static size_t _cameraID;

		// Static methods.
		static std::string _generateNameFromObjType(const Type& type);
};

using ObjectPtr = SharedPointer<Object>;


#endif // __OBJECT_HPP__
