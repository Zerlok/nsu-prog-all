#include <vector>
#include "lifeobject.h"
#include "action.h"
#include "populationmap.h"


const int LifeObject::min_ttl_to_live = 1;
const int LifeObject::max_ttl_to_live = 8;
const int LifeObject::min_damage = 0;
const int LifeObject::default_damage = 1;
const int LifeObject::max_damage = 6;
const int LifeObject::min_weight = 0;
const int LifeObject::default_weight = 1;
const int LifeObject::max_weight = 6;
const int LifeObject::min_ttl_to_reproducing = 2;
const int LifeObject::weight_ratio_at_reproducing = 2;
const int LifeObject::hp_for_murder = 2;
const Point LifeObject::view_radius = Point(1, 1);

const LifeObject LifeObject::empty = LifeObject(
		Point(-1, -1),
		0,
		LifeObject::min_damage,
		LifeObject::min_weight
);


LifeObject::LifeObject(const Point &pos, int hp, int dp, int weight)
	: _position(pos),
	  _ttl(hp),
	  _damage(dp),
	  _weight(weight),
	  _type(Type::none)
{
	if (_ttl > max_ttl_to_live)
		_ttl = max_ttl_to_live;

	if (_damage > max_damage)
		_damage = max_damage;
	else if (_damage < min_damage)
		_damage = default_damage;

	if (_weight < min_weight)
		_weight = default_weight;
}


LifeObject::LifeObject(const LifeObject &obj)
	: _position(obj._position),
	  _ttl(obj._ttl),
	  _damage(obj._damage),
	  _weight(obj._weight),
	  _type(obj._type)
{
}


LifeObject::~LifeObject()
{
}


bool LifeObject::is_alive() const
{
	return (_ttl > min_ttl_to_live);
}


int LifeObject::get_health() const
{
	return _ttl;
}


int LifeObject::get_weight() const
{
	return _weight;
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
	return is_alive();
}


LifeObject *LifeObject::clone() const
{
	return new LifeObject(*this);
}


LifeObject::Action *LifeObject::create_action(const PopulationMap &map)
{
	return nullptr;
}


LifeObject &LifeObject::operator=(const LifeObject &obj)
{
	_ttl = obj._ttl;
	_damage = obj._damage;
	_weight = obj._weight;
	_type = obj._type;

	return (*this);
}


void LifeObject::deal_damage(int dmg)
{
	_ttl -= dmg;

	if (!is_alive())
		kill();
}


void LifeObject::kill()
{
	_ttl = 0;
}
