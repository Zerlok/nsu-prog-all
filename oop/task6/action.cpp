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


bool LifeObject::Action::is_source_null() const
{
	return (_source == nullptr);
}


LifeObject &LifeObject::Action::get_source()
{
	return (*_source);
}


const LifeObject &LifeObject::Action::get_source() const
{
	return (*_source);
}


const LifeObject::Action::Type &LifeObject::Action::get_type() const
{
	return _type;
}


LifeObject::Action &LifeObject::Action::operator=(const Action &action)
{
	_source = action._source;
	_type = action._type;

	return (*this);
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
	if (_target->_weight > 0)
	{
		_target->_weight -= 1;
		_source->_weight += 1;
		_source->_ttl += 4;
	}
}


// ---------------------------- ATTACK ACTION ---------------------------- //

LifeObject::AttackAction::AttackAction()
	: LifeObject::Action(nullptr, LifeObject::Action::Type::fight),
	  _target(nullptr)
{
}


LifeObject::AttackAction::AttackAction(LifeObject *source, LifeObject *target)
	: LifeObject::Action(source, LifeObject::Action::Type::fight),
	  _target(target)
{
}


LifeObject::AttackAction::~AttackAction()
{
}


void LifeObject::AttackAction::execute(PopulationMap &map)
{
	if (_target->is_alive())
		_target->_ttl -= _source->_damage;
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
	child->_ttl = _source->_ttl / LifeObject::min_ttl_to_reproducing;
	child->_weight = _source->_weight / LifeObject::weight_ratio_at_reproducing;

	if (child->is_alive())
	{
		_source->_ttl -= child->_ttl;
		map.push_object(child);
	}
	else
		delete child;
}
