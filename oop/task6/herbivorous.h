#ifndef __HERBIVOROUS_H__
#define __HERBIVOROUS_H__


#include "point.h"
#include "lifeobject.h"
#include "populationmap.h"


class Herbivorous : public LifeObject
{
	public:
		Herbivorous(
				const Point &pos=Point(),
				int hp=min_ttl_to_live,
				int dp=default_damage,
				int weight=default_weight
		);
		Herbivorous(const Herbivorous &herbivorous);
		virtual ~Herbivorous();

		virtual LifeObject *clone() const override;
		virtual LifeObject::Action *create_action(const PopulationMap &map) override;

	private:
		bool is_hungry() const;
		bool find_food(const PopulationMap::object_list &neighbours);

		void move_to(const Point &pos);

		LifeObject *food;
};


// __HERBIVOROUS_H__
#endif
