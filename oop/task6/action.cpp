#include "action.h"


// ---------------------------- ABSTRACT ACTION ---------------------------- //

LifeObject::Action::Action()
	: _source(nullptr),
	  _type(Type::move) {}


LifeObject::Action::Action(LifeObject *source, const Type &type)
	: _source(source),
	  _type(type)
{
}


LifeObject::Action::~Action()
{
}


const LifeObject *LifeObject::Action::get_source() const
{
	return _source;
}


const LifeObject::Action::Type &LifeObject::Action::get_type() const
{
	return _type;
}


bool LifeObject::Action::operator==(const LifeObject::Action &action) const
{
	return (_type == action._type);
}


bool LifeObject::Action::operator!=(const LifeObject::Action &action) const
{
	return !((*this) == action);
}


bool LifeObject::Action::operator<(const LifeObject::Action &action) const
{
	return (_type < action._type);
}


bool LifeObject::Action::operator>(const LifeObject::Action &action) const
{
	return (action < (*this));
}


bool LifeObject::Action::operator<=(const LifeObject::Action &action) const
{
	return (((*this) < action)
			|| ((*this) == action));
}


bool LifeObject::Action::operator>=(const LifeObject::Action &action) const
{
	return (action <= (*this));
}


std::ostream &operator<<(std::ostream &out, const LifeObject::Action::Type &type)
{
	switch (type)
	{
		case LifeObject::Action::Type::reproduce:
			out << "reproduce";
			break;
		case LifeObject::Action::Type::attack:
			out << "attack";
			break;
		case LifeObject::Action::Type::eat:
			out << "eat";
			break;
		default:
		case LifeObject::Action::Type::move:
			out << "move";
			break;
	}

	return out;
}


// ---------------------------- MOVE ACTION ---------------------------- //

LifeObject::MoveAction::MoveAction()
	: LifeObject::Action(nullptr, LifeObject::Action::Type::move),
	  _position(Point::zero)
{
}


LifeObject::MoveAction::MoveAction(LifeObject *source, const Point &position)
	: LifeObject::Action(source, LifeObject::Action::Type::move),
	  _position(position)
{
}


LifeObject::MoveAction::~MoveAction()
{
}


void LifeObject::MoveAction::execute(PopulationMap &map)
{
	if (_source->is_alive()
			&& map.is_valid_position(_position))
		_source->_position = _position;
}


// ---------------------------- EAT ACTION ---------------------------- //


LifeObject::EatAction::EatAction()
	: LifeObject::Action(nullptr, LifeObject::Action::Type::eat),
	  _target(nullptr)
{
}


LifeObject::EatAction::EatAction(LifeObject *source, LifeObject *target)
	: LifeObject::Action(source, LifeObject::Action::Type::eat),
	  _target(target)
{
}


LifeObject::EatAction::~EatAction()
{
}


void LifeObject::EatAction::execute(PopulationMap &map)
{
	if (!(_source->is_alive()))
		return;

	if (_source->_position != _target->_position)
		_source->_position = _target->_position;

	if (_target->_mass > 0)
	{
		_target->_mass -= 1;
		_source->_ttl += 2;
	}
}


// ---------------------------- ATTACK ACTION ---------------------------- //

LifeObject::AttackAction::AttackAction()
	: LifeObject::Action(nullptr, LifeObject::Action::Type::attack),
	  _target(nullptr)
{
}


LifeObject::AttackAction::AttackAction(LifeObject *source, LifeObject *target)
	: LifeObject::Action(source, LifeObject::Action::Type::attack),
	  _target(target)
{
}


LifeObject::AttackAction::~AttackAction()
{
}


void LifeObject::AttackAction::execute(PopulationMap &map)
{
	if (!(_source->is_alive()
		  && _target->is_alive()))
		return;

	if (_source->_position != _target->_position)
		_source->_position = _target->_position;

	_target->deal_damage(_source->_damage);
}


// ---------------------------- REPRODUCE ACTION ---------------------------- //

LifeObject::ReproduceAction::ReproduceAction()
	: LifeObject::Action(nullptr, LifeObject::Action::Type::reproduce)
{
}


LifeObject::ReproduceAction::ReproduceAction(LifeObject *source)
	: LifeObject::Action(source, LifeObject::Action::Type::reproduce)
{
}


LifeObject::ReproduceAction::~ReproduceAction()
{
}


void LifeObject::ReproduceAction::execute(PopulationMap &map)
{
	if (!(_source->is_alive()))
		return;

	std::vector<Point> free_positions = map.get_free_positions(_source->_position);
	if (free_positions.empty())
		return;

	LifeObject *child = _source->clone();
	child->_position = free_positions[(rand() % free_positions.size())];
	child->_ttl = _source->_ttl / Config::object_min_ttl_for_reproducing;
	child->_mass = _source->_mass;

	if (child->is_alive())
	{
		_source->_ttl -= child->_ttl;
		map.insert_object(child);
	}
	else
		delete child;
}
