#include "point.h"
#include "lifeobject.h"
#include "populationmap.h"
#include "action.h"

#include "herbivorous.h"


Herbivorous::Herbivorous(const Point &pos, int hp, int dp, int weight)
	: LifeObject(pos, hp, dp, weight)
{
	this->_type = Type::herbivorous;
}


Herbivorous::~Herbivorous()
{
}


Herbivorous::Action *Herbivorous::create_action(const PopulationMap &map)
{
	make_older();

	switch (rand() % 3)
	{
		case 0:
			if (rand() % 3)
				return new ReproduceAction(this);
			break;

		case 1:
			for (LifeObject *obj : map.get_neighbours(_position))
				if (obj->get_type() == Type::plant)
					return new EatAction(this, obj);
			break;

		default:
			break;
	}

	std::vector<Point> free_positions = map.get_free_positions(_position);
	free_positions.push_back(_position);
	return new MoveAction(this, free_positions[(rand() % free_positions.size())]);
}
