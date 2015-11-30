#ifndef __HERBIVOROUS_H__
#define __HERBIVOROUS_H__


#include "lifeobject.h"


class Herbivorous : public LifeObject
{
	public:
		Herbivorous(
				const Point &pos=Point(),
				int hp=min_ttl_to_live,
				int dp=default_damage,
				int weight=default_weight
		);
		virtual ~Herbivorous();

		virtual LifeObject::Action *create_action(const PopulationMap &map) override;
};


// __HERBIVOROUS_H__
#endif
