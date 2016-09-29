#include "object.hpp"

#include <sstream>


size_t Object::_objID = 0;


std::string Object::_generateName(const Type& type)
{
	std::stringstream ss;
	switch (type)
	{
		case Type::MESH:
			ss << "Mesh";
			break;
		case Type::LAMP:
			ss << "Lamp";
			break;
		default:
			break;
	}

	ss << _objID;
	return ss.str();
}


Object::Object(const Type& type,
			   const std::string& name,
			   const Point& pos)
	: _type(type),
	  _name(name),
	  _position(pos)
{
	++_objID;
	if (_name.empty())
		_name = _generateName(_type);
}


Object::Object(const Object& obj)
	: _type(obj._type),
	  _name(obj._name),
	  _position(obj._pos)
{
	++_objID;
	if (_name.empty())
		_name = _generateName(_type);
}


Object::Object(Object&& obj)
	: _type(std::move(obj._type)),
	  _name(std::move(obj._name)),
	  _position(std::move(obj._pos))
{
}
