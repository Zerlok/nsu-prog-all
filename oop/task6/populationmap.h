#ifndef __POPULATIONMAP_H__
#define __POPULATIONMAP_H__


#include <list>
#include <vector>
#include "lifeobject.h"


class PopulationMap
{
	public:
		// Types.
		typedef std::list<LifeObject*> obj_ptr_list;
		typedef std::list<const LifeObject*> obj_const_ptr_list;

		// Constructors / Destructor.
		PopulationMap(const Point &point);
		~PopulationMap();

		// Getters.
		int get_width() const;
		int get_height() const;

		LifeObject *get(const Point &point);
		const LifeObject *get(const Point &point) const;

		const obj_ptr_list get_neighbours(const Point &point);
		const obj_const_ptr_list get_neighbours(const Point &point) const;

		const obj_ptr_list &get_objects();
		const obj_const_ptr_list &get_objects() const;

		// Methods.
		void push_object(LifeObject *obj);
		void clear_objects();

	private:
		// Fields.
		const Point &_map_corner;
		obj_ptr_list _objects;
};


// __POPULATIONMAP_H__
#endif
