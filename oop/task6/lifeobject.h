#ifndef __LIFEOBJECT_H__
#define __LIFEOBJECT_H__


#include <iostream>
#include <string>
#include <list>
#include "point.h"
#include "config.h"


class PopulationMap;


class LifeObject
{
	public:
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
		LifeObject(const Point &pos, int health, int damage, int mass);
		LifeObject(const LifeObject &obj);
		virtual ~LifeObject();

		// Getters.
		bool is_alive() const;
		bool is_eatable() const;

		const Point &get_position() const;
		int get_health() const;
		int get_damage() const;
		int get_mass() const;
		const Type &get_type() const;

		// Virtual methods.
		virtual LifeObject *clone() const;
		virtual Action *create_action(const PopulationMap &map);

		// Methods.
		void decrement_mass();

		// Operators.
		bool operator==(const LifeObject &obj) const;
		bool operator!=(const LifeObject &obj) const;
		bool operator<(const LifeObject &obj) const;
		bool operator>(const LifeObject &obj) const;
		bool operator<=(const LifeObject &obj) const;
		bool operator>=(const LifeObject &obj) const;

	protected:
		// Fields.
		Point _position;
		int _ttl; // Ticks To Live - health.
		int _damage;
		int _mass;
		Type _type;

		// Methods.
		bool make_older();
		void deal_damage(int dmg);
		virtual void kill();
};


LifeObject::Type get_type_by_name(const std::string &name);
std::ostream &operator<<(std::ostream &out, const LifeObject::Type &type);


// __LIFEOBJECT_H__
#endif
