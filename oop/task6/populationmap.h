#ifndef __POPULATIONMAP_H__
#define __POPULATIONMAP_H__


#include <list>
#include <vector>
#include "lifeobject.h"


class PopulationMap
{
	public:
		// Types.
		using object_list = std::list<LifeObject*>;

		// Constructors / Destructor.
		PopulationMap(const Point &corner_position);
		virtual ~PopulationMap();

		// Getters.
		int get_width() const;
		int get_height() const;

		bool is_valid_position(const Point &position) const;
		std::vector<Point> get_free_positions(const Point &point) const;

		object_list get_neighbours(const Point &point);
		const object_list get_neighbours(const Point &point) const;

		object_list &get_objects();
		const object_list &get_objects() const;

		// Methods.
		void push_object(LifeObject *obj);
		void clear_objects();

	private:
		// Fields.
		const Point &_corner_position;
		object_list _objects;
};


// __POPULATIONMAP_H__
#endif
