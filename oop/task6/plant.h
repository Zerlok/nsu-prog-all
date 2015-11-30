#ifndef __PLANT_H__
#define __PLANT_H__


#include "lifeobject.h"


class Plant : public LifeObject
{
	public:
		Plant(
				const Point &pos=Point(),
				int hp=min_ttl_to_live,
				int dp=default_damage,
				int weight=default_weight
		);
		virtual ~Plant();

		virtual LifeObject::Action *create_action(const PopulationMap &map) override;
};


// __PLANT_H__
#endif
