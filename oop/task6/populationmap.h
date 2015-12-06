#ifndef __POPULATIONMAP_H__
#define __POPULATIONMAP_H__


#include <list>
#include <vector>
#include "lifeobject.h"


class PopulationMap
{
	public:
		// Types.
		using objects_list = std::list<LifeObject*>;

		// Constructors / Destructor.
		PopulationMap(const Point &corner_position);
		virtual ~PopulationMap();

		// Getters.
		int get_width() const;
		int get_height() const;
		int get_plants_num() const;
		int get_herbivorous_num() const;
		int get_predators_num() const;

		bool is_valid_position(const Point &position) const;

		std::vector<Point> get_free_positions(const Point &point) const;
		std::vector<Point> get_move_positions(const Point &point) const;

		objects_list get_neighbours(const Point &point);
		const objects_list get_neighbours(const Point &point) const;

		objects_list &get_objects();
		const objects_list &get_objects() const;

		// Methods.
		void insert_object(LifeObject *obj);
		objects_list::iterator erase_object(objects_list::iterator &it);
		void clear_objects();

		Point validate_position(const Point &position) const;

	private:
		// Fields.
		const Point _corner_position;
		objects_list _objects;

		int _plants_num;
		int _herbivorous_num;
		int _predators_num;
};


// __POPULATIONMAP_H__
#endif
