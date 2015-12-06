#include "action.h"

#include "predator.h"



Predator::Predator(const Point &pos, int hp, int dp, int weight)
	: LifeObject(pos, hp, dp, weight),
	  food(nullptr),
	  victim(nullptr)
{
	this->_type = Type::predator;
}


Predator::Predator(const Predator &predator)
	: LifeObject(predator._position, predator._ttl, predator._damage, predator._mass),
	  food(nullptr),
	  victim(nullptr)
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

	if (!is_hungry()
			&& (rand() % 2))
		return new ReproduceAction(this);

	if (is_hungry())
	{
		const PopulationMap::objects_list &neighbours = map.get_neighbours(_position);
		if (find_food(neighbours))
			return new EatAction(this, food);

		else if (find_victim(neighbours))
			return new AttackAction(this, victim);
	}

	std::vector<Point> available_moves = map.get_move_positions(_position);
	available_moves.push_back(_position);
	return new MoveAction(this, available_moves[(rand() % available_moves.size())]);
}


bool Predator::is_hungry() const
{
	return (this->_ttl <= 5);
}


bool Predator::find_food(const PopulationMap::objects_list &neighbours)
{
	food = nullptr;
	for (LifeObject *obj : neighbours)
		if ((obj->get_type() == Type::herbivorous)
				&& !(obj->is_alive())
				&& ((food == nullptr)
					|| (obj->get_weight() > food->get_weight())))
			food = obj;

	return (food != nullptr);
}


bool Predator::find_victim(const PopulationMap::objects_list &neighbours)
{
	victim = nullptr;
	for (LifeObject *obj : neighbours)
		if ((obj->get_type() == Type::herbivorous)
				&& obj->is_alive()
				&& ((victim == nullptr)
						|| (obj->get_health() < victim->get_health())))
			victim = obj;

	return (victim != nullptr);
}
