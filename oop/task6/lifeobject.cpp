#include <vector>
#include "lifeobject.h"
#include "action.h"
#include "populationmap.h"


LifeObject::LifeObject(const Point &pos, int health, int damage, int mass)
	: _position(pos),
	  _ttl(health),
	  _damage(damage),
	  _mass(mass),
	  _type(Type::none)
{
	if (_damage < Config::object_min_damage)
		_damage = Config::object_min_damage;

	if (_mass < Config::object_min_mass)
		_mass = Config::object_min_mass;
}


LifeObject::LifeObject(const LifeObject &obj)
	: _position(obj._position),
	  _ttl(obj._ttl),
	  _damage(obj._damage),
	  _mass(obj._mass),
	  _type(obj._type)
{
}


LifeObject::~LifeObject()
{
}


bool LifeObject::is_alive() const
{
	return (_ttl > Config::object_dead_ttl);
}


bool LifeObject::is_eatable() const
{
	return (_mass > Config::object_min_mass);
}


int LifeObject::get_health() const
{
	return _ttl;
}


int LifeObject::get_damage() const
{
	return _damage;
}


int LifeObject::get_mass() const
{
	return _mass;
}


const LifeObject::Type &LifeObject::get_type() const
{
	return _type;
}


const Point &LifeObject::get_position() const
{
	return _position;
}


bool LifeObject::make_older()
{
	if (!is_alive())
		return false;

	--_ttl;

	if (!is_alive())
	{
		kill();
		return false;
	}

	return true;
}


LifeObject *LifeObject::clone() const
{
	return new LifeObject(*this);
}


LifeObject::Action *LifeObject::create_action(const PopulationMap &map)
{
	return nullptr;
}


void LifeObject::decrement_mass()
{
	--_mass;
}


bool LifeObject::operator==(const LifeObject &obj) const
{
	return (_type == obj._type);
}


bool LifeObject::operator!=(const LifeObject &obj) const
{
	return !((*this) == obj);
}


bool LifeObject::operator<(const LifeObject &obj) const
{
	return (_type < obj._type);
}


bool LifeObject::operator>(const LifeObject &obj) const
{
	return (obj < (*this));
}


bool LifeObject::operator<=(const LifeObject &obj) const
{
	return (((*this) < obj)
			|| ((*this) == obj));
}


bool LifeObject::operator>=(const LifeObject &obj) const
{
	return (obj <= (*this));
}


void LifeObject::deal_damage(int dmg)
{
	_ttl -= dmg;

	if (!is_alive())
		kill();
}


void LifeObject::kill()
{
	_ttl = Config::object_dead_ttl;
}


LifeObject::Type get_type_by_name(const std::string &name)
{
	if (!name.compare("Plant"))
		return LifeObject::Type::plant;
	else if (!name.compare("Herbivorous"))
		return LifeObject::Type::herbivorous;
	else if (!name.compare("Predator"))
		return LifeObject::Type::predator;

	return LifeObject::Type::none;
}


std::ostream &operator<<(std::ostream &out, const LifeObject::Type &type)
{
	switch (type)
	{
		case LifeObject::Type::plant:
			out << "Plant";
			break;
		case LifeObject::Type::herbivorous:
			out << "Herbivorous";
			break;
		case LifeObject::Type::predator:
			out << "Predator";
			break;

		default:
		case LifeObject::Type::none:
			out << "None";
			break;
	}

	return out;
}


std::istream &operator>>(std::istream &in, LifeObject::Type &type)
{
	std::string str;
	in >> str;
	type = get_type_by_name(str);

	return in;
}
