#ifndef __LIFEOBJECT_ACTION_H__
#define __LIFEOBJECT_ACTION_H__


#include "point.h"
#include "lifeobject.h"
#include "populationmap.h"


class LifeObject::Action
{
	public:
		// Static.
		enum class Type
		{
			move = 0,
			eat,
			fight,
			reproduce,
		};

		// Constructors / Destructor.
		Action();
		Action(LifeObject *source, const Type &type);
		virtual ~Action();

		// Virtual methods.
		virtual void execute(PopulationMap &map) = 0;

		// Operators.
		bool operator<(const LifeObject::Action &action) const;
		bool operator>(const LifeObject::Action &action) const;

	protected:
		// Fields.
		LifeObject *_source;
		Type _type;
};


class LifeObject::MoveAction : public LifeObject::Action
{
	public:
		MoveAction();
		MoveAction(LifeObject *source, const Point &position);
		virtual ~MoveAction();

		virtual void execute(PopulationMap &map) override;

	private:
		Point _position;
};


class LifeObject::EatAction : public LifeObject::Action
{
	public:
		EatAction();
		EatAction(LifeObject *source, LifeObject *target);
		virtual ~EatAction();

		virtual void execute(PopulationMap &map) override;

	private:
		LifeObject *_target;
};


class LifeObject::AttackAction : public LifeObject::Action
{
	public:
		AttackAction();
		AttackAction(LifeObject *source, LifeObject *target);
		virtual ~AttackAction();

		virtual void execute(PopulationMap &map) override;

	private:
		LifeObject *_target;
};


class LifeObject::ReproduceAction : public LifeObject::Action
{
	public:
		ReproduceAction();
		ReproduceAction(LifeObject *source);
		virtual ~ReproduceAction();

		virtual void execute(PopulationMap &map) override;
};


// __LIFEOBJECT_ACTION_H__
#endif
