#include "point.h"
#include "lifeobject.h"
#include "populationmap.h"
#include "action.h"

#include "predator.h"



Predator::Predator(const Point &pos, int hp, int dp, int weight)
	: LifeObject(pos, hp, dp, weight)
{
	this->_type = Type::predator;
}


Predator::Predator(const Predator &predator)
	: LifeObject(predator._position, predator._ttl, predator._damage, predator._weight)
{
	this->_type = predator._type;
}


Predator::~Predator()
{
}


LifeObject *Predator::clone() const
{
	return new Predator(*this);
}


Predator::Action *Predator::create_action(const PopulationMap &map)
{
	if (!is_alive())
		return nullptr;

	make_older();
	const PopulationMap::object_list &neighbours = map.get_neighbours(_position);

	switch (rand() % 3)
	{
		case 0:
			if (!(rand() % 2))
				return new ReproduceAction(this);
			break;

		case 1:
			for (LifeObject *obj : neighbours)
				if (obj->get_type() == Type::herbivorous)
					if (obj->is_alive())
						return new AttackAction(this, obj);
					else
						return new EatAction(this, obj);
			break;

		default:
			break;
	}

	std::vector<Point> free_positions = map.get_free_positions(_position);
	free_positions.push_back(_position);
	return new MoveAction(this, free_positions[(rand() % free_positions.size())]);
}
