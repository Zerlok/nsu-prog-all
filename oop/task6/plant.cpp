#include "point.h"
#include "lifeobject.h"
#include "populationmap.h"
#include "action.h"

#include "plant.h"


Plant::Plant(const Point &pos, int health, int damage, int mass)
	: LifeObject(pos, health, damage, mass)
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

	if (Config::plant_is_dieable)
		make_older();

	std::vector<Point> free_positions = map.get_free_positions(_position);
	if (!(rand() % Config::plant_reproduction_ratio)
			&& (!free_positions.empty()))
	{
		return new PlantReproduceAction(this, free_positions[(rand() % free_positions.size())]);
	}

	return nullptr;
}


void Plant::kill()
{
	_ttl = Config::object_dead_ttl;
	_mass = Config::object_min_mass;
}


PlantReproduceAction::PlantReproduceAction()
{
}


PlantReproduceAction::PlantReproduceAction(LifeObject *source, const Point &position)
	: ReproduceAction(source, position)
{
}


PlantReproduceAction::~PlantReproduceAction()
{
}


LifeObject *PlantReproduceAction::create_child()
{
	return new Plant(_position, Config::plant_born_ttl);
}
