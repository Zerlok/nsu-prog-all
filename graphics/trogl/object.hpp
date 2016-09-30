#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__


#include <string>

#include "common/point.hpp"


class Object
{
	public:
		enum class Type
		{
			MESH = 'M',
			LAMP = 'L',
		};

		Object(const Type& type,
			   const Point& pos = Point::zero,
			   const std::string& name = std::string());
		Object(const Object& obj);
		Object(Object&& obj);
		virtual ~Object();

		const Point& getPosition() const;
		void setPosition(const Point& position);

		const Point& getRotation() const;
		void setRotation(const Point& rotation);

		const Point& getScale() const;
		void setScale(const Point& scale);

		const std::string& getName() const;
		void setName(const std::string& name);

	protected:
		Type _type;

		Point _position;
		Point _rotation;
		Point _scale;

		std::string _name;

	private:
		static size_t _objID;
		static std::string _generateName(const Type& type);
};


#endif // __OBJECT_HPP__
