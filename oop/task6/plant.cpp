#include "point.h"
#include "lifeobject.h"
#include "populationmap.h"
#include "action.h"

#include "plant.h"


Plant::Plant(const Point &pos, int hp, int dp, int m)
	: LifeObject(pos, hp, dp, m)
{
	this->_type = Type::plant;
}


Plant::Plant(const Plant &plant)
	: LifeObject(plant._position, plant._ttl, plant._damage, plant._mass)
{
	this->_type = plant._type;
}


Plant::~Plant()
{
}


LifeObject *Plant::clone() const
{
	return new Plant(*this);
}


Plant::Action *Plant::create_action(const PopulationMap &map)
{
	if (!is_alive())
		return nullptr;

	_ttl = _mass + 1;
	if (!(rand() % 4))
		return new ReproduceAction(this);

	return nullptr;
}
