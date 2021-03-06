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
		PopulationMap(int width, int height);
		PopulationMap(const PopulationMap &&map);
		virtual ~PopulationMap();

		// Getters.
		int get_width() const;
		int get_height() const;
		int get_plants_num() const;
		int get_herbivorous_num() const;
		int get_predators_num() const;
		int get_total_objects_num() const;

		bool is_valid_position(const Point &position) const;

		std::vector<Point> get_free_positions(
				const Point &point,
				bool except_plants = true,
				bool except_herbivorous = true,
				bool except_preadators = true
		) const;

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

		int _plants_num;
		int _herbivorous_num;
		int _predators_num;

		objects_list _objects;
};


// __POPULATIONMAP_H__
#endif
