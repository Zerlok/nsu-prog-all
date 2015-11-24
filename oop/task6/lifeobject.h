#ifndef __LIFEOBJECT_H__
#define __LIFEOBJECT_H__


#include <list>
#include "point.h"


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

		static const LifeObject empty;

		enum class State
		{
			sleeping = 0,
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
		class Action
		{
			public:
				// Static.
				enum class Type
				{
					sleep = 0,
					fight = 1,
					reproduce = 2,
					eat = 3,
					die = 4,
					move = 5,
				};

				// Constructors / Destructor.
				Action()
					: _source(nullptr),
					  _type(Type::sleep),
					  _local_position(0, 0) {}
				Action(LifeObject *source, const Type &type, const Point &local_pos)
					: _source(source),
					  _type(type),
					  _local_position(local_pos) {}
				Action(const Action &action)
					: _source(action._source),
					  _type(action._type),
					  _local_position(action._local_position) {}
				~Action() {}

				// Getters.
				bool is_null() const { return (_source == nullptr); }
				LifeObject &get_source() { return (*_source); }
				const LifeObject &get_source() const { return (*_source); }

				const Type &get_type() const { return _type; }

				const Point &get_local_position() const { return _local_position; }

				// Operators.
				Action &operator=(const Action &action)
				{
					_source = action._source;
					_type = action._type;
					_local_position = action._local_position;

					return (*this);
				}

			protected:
				// Fields.
				LifeObject *_source;
				Type _type;
				Point _local_position;
		};

		// Constructors / Destructor.
		LifeObject(const Point &pos, int hp=min_ttl_to_live, int dp=default_damage, int weight=default_weight);
		LifeObject(const LifeObject &obj);
		~LifeObject();

		// Getters.
		bool is_alive() const;
		int get_health() const;
		int get_weight() const;
		const State &get_state() const;
		const Type &get_type() const;
		const Point &get_position() const;

		// Methods.
		bool attack(LifeObject &target);
		bool eat(int hp);
		LifeObject reproduce();
		bool move_to(const Point &point);
		bool make_older();

		void reset_state();

		// Virtual methods.
		virtual Action make_action(const std::list<LifeObject *> &neighbours);

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


// __LIFEOBJECT_H__
#endif
