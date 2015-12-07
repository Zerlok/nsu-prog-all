#ifndef __PLANT_H__
#define __PLANT_H__


#include "config.h"
#include "lifeobject.h"


class Plant : public LifeObject
{
	public:
		Plant(
				const Point &pos,
				int health = Config::plant_born_ttl,
				int damage = Config::plant_damage,
				int mass = Config::plant_mass
		);
		Plant(const Plant &plant);
		virtual ~Plant();

		virtual LifeObject *clone() const override;
		virtual LifeObject::Action *create_action(const PopulationMap &map) override;
};


// __PLANT_H__
#endif
