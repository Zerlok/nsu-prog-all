#include "point.h"
#include "lifeobject.h"
#include "populationmap.h"
#include "action.h"

#include "plant.h"


Plant::Plant(const Point &pos, int hp, int dp, int weight)
	: LifeObject(pos, hp, dp, weight)
{
	this->_type = Type::plant;
}


Plant::Plant(const Plant &plant)
	: LifeObject(plant._position, plant._ttl, plant._damage, plant._weight)
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

	if (!(rand() % 5))
		return new ReproduceAction(this);

	return nullptr;
}
