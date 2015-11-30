#ifndef __PREDATOR_H__
#define __PREDATOR_H__


#include "lifeobject.h"


class Predator : public LifeObject
{
	public:
		Predator(
				const Point &pos=Point(),
				int hp=min_ttl_to_live,
				int dp=default_damage,
				int weight=default_weight
		);
		virtual ~Predator();

		virtual LifeObject::Action *create_action(const PopulationMap &map) override;
};


// __PREDATOR_H__
#endif
