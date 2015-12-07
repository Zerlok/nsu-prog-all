#ifndef __HERBIVOROUS_H__
#define __HERBIVOROUS_H__


#include "config.h"
#include "point.h"
#include "lifeobject.h"
#include "populationmap.h"


class Herbivorous : public LifeObject
{
	public:
		Herbivorous(
				const Point &pos,
				int health = Config::herbivorous_born_ttl,
				int damage = Config::herbivorous_damage,
				int mass = Config::herbivorous_mass
		);
		Herbivorous(const Herbivorous &herbivorous);
		virtual ~Herbivorous();

		virtual LifeObject *clone() const override;
		virtual LifeObject::Action *create_action(const PopulationMap &map) override;

	private:
		bool is_hungry() const;
		bool find_food(const PopulationMap::objects_list &neighbours);

		void move_to(const Point &pos);

		LifeObject *food;
};


// __HERBIVOROUS_H__
#endif
