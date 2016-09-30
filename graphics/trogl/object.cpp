#include "object.hpp"

#include <sstream>

#include <logger.hpp>


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
			   const Point& pos,
			   const std::string& name)
	: _type(type),
	  _position(pos),
	  _name(name)
{
	++_objID;
	if (_name.empty())
		_name = _generateName(_type);

	logDebug << _name << " (" << _objID << ") object created" << logEnd;
}


Object::Object(const Object& obj)
	: _type(obj._type),
	  _position(obj._position),
	  _name(obj._name)
{
	++_objID;
	if (_name.empty())
		_name = _generateName(_type);

	logDebug << _name << " (" << _objID << ") object copied" << logEnd;
}


Object::Object(Object&& obj)
	: _type(std::move(obj._type)),
	  _position(std::move(obj._position)),
	  _name(std::move(obj._name))
{
	logDebug << _name << " (" << _objID << ") object moved" << logEnd;
}


Object::~Object()
{
	logDebug << _name << " object removed" << logEnd;
}


const Point&Object::getPosition() const
{
	return _position;
}


void Object::setPosition(const Point& position)
{
	_position = position;
}


const Point& Object::getRotation() const
{
	return _rotation;
}


void Object::setRotation(const Point& rotation)
{
	_rotation = rotation;
}


const Point& Object::getScale() const
{
	return _scale;
}


void Object::setScale(const Point& scale)
{
	_scale = scale;
}


const std::string& Object::getName() const
{
	return _name;
}


void Object::setName(const std::string& name)
{
	_name = name;
}
