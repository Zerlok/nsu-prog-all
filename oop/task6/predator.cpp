#include "action.h"

#include "predator.h"



Predator::Predator(const Point &pos, int health, int damage, int mass)
	: LifeObject(pos, health, damage, mass),
	  food(nullptr),
	  victim(nullptr)
{
	_type = Type::predator;
}


Predator::Predator(const Predator &predator)
	: LifeObject(predator._position, predator._ttl, predator._damage, predator._mass),
	  food(nullptr),
	  victim(nullptr)
{
	_type = predator._type;
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

	if (is_hungry())
	{
		const PopulationMap::objects_list &neighbours = map.get_neighbours(_position);
		if (find_food(neighbours))
			return new EatAction(this, food);

		else if (find_victim(neighbours))
			return new AttackAction(this, victim);
	}

	std::vector<Point> free_positions = map.get_free_positions(_position, false, true, true);

	if (!is_hungry()
			&& !(rand() % Config::predator_reproduction_ratio)
			&& (!free_positions.empty()))
		return new ReproduceAction(this, free_positions[rand() % free_positions.size()]);

	free_positions.push_back(_position);
	return new MoveAction(this, free_positions[(rand() % free_positions.size())]);
}


bool Predator::is_hungry() const
{
	return (_ttl <= Config::predator_hungry_ttl);
}


bool Predator::find_food(const PopulationMap::objects_list &neighbours)
{
	food = nullptr;
	for (LifeObject *obj : neighbours)
		if ((obj->get_type() == Type::herbivorous)
				&& !(obj->is_alive())
				&& ((food == nullptr)
					|| (obj->get_mass() > food->get_mass())))
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
