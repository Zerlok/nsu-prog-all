#include "point.h"
#include "lifeobject.h"
#include "populationmap.h"
#include "action.h"

#include "herbivorous.h"


Herbivorous::Herbivorous(const Point &pos, int health, int damage, int mass)
	: LifeObject(pos, health, damage, mass),
	  food(nullptr)
{
	_type = Type::herbivorous;
}


Herbivorous::Herbivorous(const Herbivorous &herbivorous)
	: LifeObject(herbivorous._position, herbivorous._ttl, herbivorous._damage, herbivorous._mass),
	  food(nullptr)
{
	_type = herbivorous._type;
}


Herbivorous::~Herbivorous()
{
}


LifeObject *Herbivorous::clone() const
{
	return new Herbivorous(*this);
}


Herbivorous::Action *Herbivorous::create_action(const PopulationMap &map)
{
	if (!is_alive())
		return nullptr;

	make_older();


	if (is_hungry())
	{
		const PopulationMap::objects_list &neighbours = map.get_neighbours(_position);
		if (find_food(neighbours))
			return new EatAction(this, food);
	}

	std::vector<Point> free_positions = map.get_free_positions(_position, false, true, true);

	if (!is_hungry()
			&& !(rand() % Config::herbivorous_reproduction_ratio)
			&& (!free_positions.empty()))
		return new ReproduceAction(this, free_positions[(rand() % free_positions.size())]);

	free_positions.push_back(_position);
	return new MoveAction(this, free_positions[(rand() % free_positions.size())]);
}


bool Herbivorous::is_hungry() const
{
	return (_ttl <= Config::herbivorous_hungry_ttl);
}


bool Herbivorous::find_food(const PopulationMap::objects_list &neighbours)
{
	food = nullptr;
	for (LifeObject *obj : neighbours)
		if ((obj->get_type() == Type::plant)
				&& ((food == nullptr)
					|| (obj->get_mass() > food->get_mass())))
			food = obj;

	return (food != nullptr);
}

