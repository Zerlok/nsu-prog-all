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
			   const std::string& name,
			   const Point& pos = Point::zero);
		Object(const Object& obj);
		Object(Object&& obj);
		virtual ~Object();

		const Point& getPosition() const;
		void setPosition(const Point& point);

		const std::string& getName() const;
		void setName(const std::string& name);

	protected:
		const Type& _type;
		std::string _name;
		Point _position;

	private:
		static size_t _objID;
		static std::string _generateName(const Type& type);
};


#endif // __OBJECT_HPP__
