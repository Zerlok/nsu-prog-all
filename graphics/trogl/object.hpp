#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__


#include <string>
#include <glm/glm.hpp>
#include <sharedpointer.h>
#include "component.hpp"


class Object : public Component
{
	public:
		enum class Type
		{
			MESH = 'M',
			LIGHT = 'L',
			CAMERA = 'C',
		};

		Object(const Type& type,
			   const std::string& name = DEFAULT_NAME,
			   const glm::vec3& pos = glm::vec3());
		Object(const Object& obj);
		Object(Object&& obj);
		virtual ~Object();

		Object& operator=(const Object& obj);
		Object& operator=(Object&& obj);

		const Type& getObjectType() const;

		const glm::vec3& getPosition() const;
		const glm::vec3& getRotation() const;
		const glm::vec3& getScale() const;

		virtual void setPosition(const glm::vec3& position);
		virtual void setRotation(const glm::vec3& rotation);
		virtual void setScale(const glm::vec3& scale);

		virtual void applyPosition();
		virtual void applyRotation();
		virtual void applyScale();

	private:
		Type _object_type;

	protected:
		static const std::string DEFAULT_NAME;
		static const glm::vec3 DEFAULT_POSITION;
		static const glm::vec3 DEFAULT_ROTATION;
		static const glm::vec3 DEFAULT_SCALE;

		static const glm::vec3 AXIS_X;
		static const glm::vec3 AXIS_Y;
		static const glm::vec3 AXIS_Z;

		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;

	private:
		static size_t _objID;
		static std::string _generateNameFromObjType(const Type& type, const size_t& id);
};

using ObjectPtr = SharedPointer<Object>;


#endif // __OBJECT_HPP__
