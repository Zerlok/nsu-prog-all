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


Plant::~Plant()
{
}


Plant::Action *Plant::create_action(const PopulationMap &map)
{
	if (rand() % 5)
		return new ReproduceAction(this);

	return nullptr;
}
