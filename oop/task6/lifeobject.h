#ifndef __LIFEOBJECT_H__
#define __LIFEOBJECT_H__


#include <list>
#include "point.h"


class PopulationMap;


class LifeObject
{
	public:
		// Static.
		static const int min_ttl_to_live;
		static const int max_ttl_to_live;
		static const int min_damage;
		static const int default_damage;
		static const int max_damage;
		static const int min_weight;
		static const int default_weight;
		static const int max_weight;
		static const int min_ttl_to_reproducing;
		static const int weight_ratio_at_reproducing;
		static const int hp_for_murder;
		static const Point view_radius;

		static const LifeObject empty;

		enum class State
		{
			resting = 0,
			fighting = 1,
			reproducing = 2,
			eating = 3,
			dying = 4
		};

		enum class Type
		{
			none = 0,
			plant = 1,
			herbivorous = 2,
			predator = 3
		};

		// Subclass.
		class Action;

		// Constructors / Destructor.
		LifeObject(
				const Point &pos=Point(),
				int hp=min_ttl_to_live,
				int dp=default_damage,
				int weight=default_weight
		);
		LifeObject(const LifeObject &obj);
		virtual ~LifeObject();

		// Getters.
		bool is_alive() const;
		int get_health() const;
		int get_weight() const;
		const Point &get_position() const;
		const State &get_state() const;
		const Type &get_type() const;

		// Methods.
		bool move_to(const Point &point);
		bool make_older();
		void reset_state();

		// Virtual methods.
		virtual Action make_action(const PopulationMap &map);
		virtual bool attack(LifeObject &target) { return false; }
		virtual bool eat(LifeObject &target) { return false; }
		virtual LifeObject reproduce() { return LifeObject(LifeObject::empty); }

		// Operators.
		LifeObject &operator=(const LifeObject &obj);

	protected:
		// Fields.
		Point _position;
		int _ttl; // Ticks To Live - health.
		int _damage;
		int _weight;
		State _state;
		Type _type;

	private:
		// Methods.
		void deal_damage(int dmg);
		void kill();
};


class LifeObject::Action
{
	public:
		// Static.
		enum class Type
		{
			move = 0,
			fight = 1,
			reproduce = 2,
			eat = 3,
			die = 4,
		};

		// Constructors / Destructor.
		Action()
			: _source(nullptr),
			  _target(nullptr),
			  _target_position(Point::zero),
			  _type(Type::move) {}
		Action(LifeObject *source, LifeObject *target, const Type &type)
			: _source(source),
			  _target(target),
			  _target_position(target->get_position()),
			  _type(type) {}
		Action(LifeObject *source, const Point &local_pos, const Type &type)
			: _source(source),
			  _target(nullptr),
			  _target_position(local_pos),
			  _type(type) {}
		Action(const Action &action)
			: _source(action._source),
			  _target(action._target),
			  _target_position(action._target_position),
			  _type(action._type) {}
		virtual ~Action() {}

		// Getters.
		bool is_source_null() const { return (_source == nullptr); }
		bool is_target_null() const { return (_target == nullptr); }

		LifeObject &get_source() { return (*_source); }
		LifeObject &get_target() { return (*_target); }

		const LifeObject &get_source() const { return (*_source); }
		const LifeObject &get_target() const { return (*_target); }
		const Point &get_target_position() const { return _target_position; }
		const Type &get_type() const { return _type; }

		// Operators.
		Action &operator=(const Action &action)
		{
			_source = action._source;
			_target = action._target;
			_target_position = action._target_position;
			_type = action._type;

			return (*this);
		}

	protected:
		// Fields.
		LifeObject *_source;
		LifeObject *_target;
		Point _target_position;
		Type _type;
};


// __LIFEOBJECT_H__
#endif
