#include "component.hpp"


#include <sstream>
#include <iomanip>
#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


size_t Component::_globID = 0;


Component::Component(const Component::Type& t,
					 const std::string& name)
	: Animatable(name),
	  _type(t),
	  _id(++_globID)
{
	logDebug << (*this) << " created." << logEndl;
}


Component::Component(const Component& c)
	: Animatable(c),
	  _type(c._type),
	  _id(++_globID)
{
	logDebug << (*this) << " copied from " << c << logEndl;
}


Component::Component(Component&& c)
	: Animatable(std::move(c)),
	  _type(std::move(c._type)),
	  _id(std::move(c._id))
{
	logDebug << (*this) << " moved." << logEndl;
}


Component::~Component()
{
	logDebug << (*this) << " removed." << logEndl;
}


Component& Component::operator=(const Component& c)
{
	Animatable::operator=(c);
	_type = c._type;
	_id = c._id;

	logDebug << (*this) << " copied from " << c << logEndl;
	return (*this);
}


Component& Component::operator=(Component&& c)
{
	Animatable::operator=(std::move(c));
	_type = std::move(c._type);
	_id = std::move(c._id);

	logDebug << (*this) << " moved." << logEndl;
	return (*this);
}


bool Component::operator==(const Component& c) const
{
	return (_id == c._id);
}


bool Component::operator!=(const Component& c) const
{
	return (_id != c._id);
}


bool Component::operator<(const Component& c) const
{
	return (_id < c._id);
}


bool Component::operator>(const Component& c) const
{
	return (_id > c._id);
}


/*
Component& Component::operator+=(const Component& c)
{
	return (*this);
}

Component& Component::operator*=(const float& ratio)
{
	return (*this);
}


Component Component::operator+(const Component& c) const
{
	return (*this);
}


Component Component::operator*(const float& ratio) const
{
	return (*this);
}
*/


const size_t& Component::getId() const
{
	return _id;
}


const Component::Type& Component::getType() const
{	
	return _type;
}


Component& Component::toComponent()
{
	return (*this);
}


const Component& Component::toComponent() const
{
	return (*this);
}


std::string Component::toString() const
{
	return getName();
}


std::ostream& operator<<(std::ostream& out, const Component& c)
{
	out << "<Component"
		<< c._id << " "
		<< c.getName() << ">";

	return out;
}


size_t Component::Hash::operator()(const Component& c) const
{
	return std::hash<size_t>()(c.getId());
}
