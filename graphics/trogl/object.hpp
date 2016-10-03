#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__


#include <string>
#include <glm/glm.hpp>
#include "component.hpp"


class Object : public Component
{
	public:
		enum class Type
		{
			MESH = 'M',
			LAMP = 'L',
			CAMERA = 'C',
		};

		Object(const Type& type,
			   const std::string& name = DEFAULT_NAME,
			   const glm::vec3& pos = glm::vec3());
		Object(const Object& obj);
		Object(Object&& obj);
		virtual ~Object();

		const Type& getObjectType() const;

		const glm::vec3& getPosition() const;
		void setPosition(const glm::vec3& position);

		const glm::vec3& getRotation() const;
		void setRotation(const glm::vec3& rotation);

		const glm::vec3& getScale() const;
		void setScale(const glm::vec3& scale);

	private:
		Type _object_type;

	protected:
		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;

	private:
		static const std::string DEFAULT_NAME;
		static std::string generateNameFromObjType(const Type& type, const size_t& id);
		static size_t objID;
};


#endif // __OBJECT_HPP__
