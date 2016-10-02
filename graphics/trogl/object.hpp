#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__


#include <string>
#include "common/point.hpp"
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
			   const Point& pos = Point::zero);
		Object(const Object& obj);
		Object(Object&& obj);
		virtual ~Object();

		const Type& getObjectType() const;

		const Point& getPosition() const;
		void setPosition(const Point& position);

		const Point& getRotation() const;
		void setRotation(const Point& rotation);

		const Point& getScale() const;
		void setScale(const Point& scale);

	private:
		Type _object_type;

	protected:
		Point _position;
		Point _rotation;
		Point _scale;

	private:
		static const std::string DEFAULT_NAME;
		static std::string generateNameFromObjType(const Type& type, const size_t& id);
		static size_t objID;
};


#endif // __OBJECT_HPP__
