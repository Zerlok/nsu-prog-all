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

	if (_target->_mass > Config::object_min_mass)
	{
		--_target->_mass;
		_source->_ttl += Config::object_ttl_for_eating;
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
	if (!(_source->is_alive())
			|| !(_target->is_alive()))
		return;

	if (_source->_position != _target->_position)
		_source->_position = _target->_position;

	_target->deal_damage(_source->_damage);
}


// ---------------------------- REPRODUCE ACTION ---------------------------- //

LifeObject::ReproduceAction::ReproduceAction()
	: LifeObject::Action(nullptr, LifeObject::Action::Type::reproduce),
	  _position(Point::zero)
{
}


LifeObject::ReproduceAction::ReproduceAction(LifeObject *source, const Point &position)
	: LifeObject::Action(source, LifeObject::Action::Type::reproduce),
	  _position(position)
{
}


LifeObject::ReproduceAction::~ReproduceAction()
{
}


void LifeObject::ReproduceAction::execute(PopulationMap &map)
{
	if (!(_source->is_alive())
			|| !(map.is_valid_position(_position))
			|| (_source->_ttl < Config::object_min_ttl_for_reproducing))
		return;

	LifeObject *child = create_child();

	if (child->is_alive())
	{
		_source->_ttl -= Config::object_parent_ttl_reproduction_ratio;
		map.insert_object(child);
	}
	else
		delete child;
}


LifeObject *LifeObject::ReproduceAction::create_child()
{
	LifeObject *child = _source->clone();
	child->_position = _position;
	child->_ttl = _source->_ttl / Config::object_child_ttl_reproduction_ratio;

	return child;
}
