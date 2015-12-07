#ifndef __PREDATOR_H__
#define __PREDATOR_H__


#include "config.h"
#include "point.h"
#include "lifeobject.h"
#include "populationmap.h"


class Predator : public LifeObject
{
	public:
		Predator(
				const Point &pos,
				int health = Config::predator_born_ttl,
				int damage = Config::predator_damage,
				int mass = Config::herbivorous_mass
		);
		Predator(const Predator &predator);
		virtual ~Predator();

		virtual LifeObject *clone() const override;
		virtual LifeObject::Action *create_action(const PopulationMap &map) override;

	private:
		bool is_hungry() const;
		bool find_food(const PopulationMap::objects_list &neighbours);
		bool find_victim(const PopulationMap::objects_list &neighbours);

		void move_to(const Point &pos);

		LifeObject *food;
		LifeObject *victim;
};


// __PREDATOR_H__
#endif
