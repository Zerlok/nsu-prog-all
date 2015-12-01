#include "point.h"
#include "lifeobject.h"
#include "populationmap.h"
#include "action.h"

#include "herbivorous.h"


Herbivorous::Herbivorous(const Point &pos, int hp, int dp, int weight)
	: LifeObject(pos, hp, dp, weight),
	  food(nullptr)
{
	this->_type = Type::herbivorous;
}


Herbivorous::Herbivorous(const Herbivorous &herbivorous)
	: LifeObject(herbivorous._position, herbivorous._ttl, herbivorous._damage, herbivorous._weight),
	  food(nullptr)
{
	this->_type = herbivorous._type;
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

	if (!is_hungry()
			&& (rand() % 2))
		return new ReproduceAction(this);

	if (is_hungry())
	{
		const PopulationMap::object_list &neighbours = map.get_neighbours(_position);
		if (find_food(neighbours))
		{
	//			move_to(food->_position);
			return new EatAction(this, food);
		}
	}

	std::vector<Point> free_positions = map.get_free_positions(_position);
	free_positions.push_back(_position);
	return new MoveAction(this, free_positions[(rand() % free_positions.size())]);
}


bool Herbivorous::is_hungry() const
{
	return (this->_ttl <= 5);
}


bool Herbivorous::find_food(const PopulationMap::object_list &neighbours)
{
	food = nullptr;
	for (LifeObject *obj : neighbours)
		if ((obj->get_type() == Type::plant)
				&& ((food == nullptr)
					|| (obj->get_weight() > food->get_weight())))
			food = obj;

	return (food != nullptr);
}

