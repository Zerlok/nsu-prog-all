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

		enum class Type
		{
			none = 0,
			plant = 1,
			herbivorous = 2,
			predator = 3
		};

		// LifeObject Available Actions.
		class Action;
		class MoveAction;
		class EatAction;
		class AttackAction;
		class ReproduceAction;

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
		const Type &get_type() const;

		// Methods.

		// Virtual methods.
		virtual Action *create_action(const PopulationMap &map);

		// Operators.
		LifeObject &operator=(const LifeObject &obj);

	protected:
		// Fields.
		Point _position;
		int _ttl; // Ticks To Live - health.
		int _damage;
		int _weight;
		Type _type;

		// Methods.
		bool make_older();
		void deal_damage(int dmg);
		void kill();
};


// __LIFEOBJECT_H__
#endif
