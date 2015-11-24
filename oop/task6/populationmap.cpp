#include "populationmap.h"


PopulationMap::PopulationMap(const Point &point)
	: _map_corner(point)
{
}


PopulationMap::~PopulationMap()
{
}


LifeObject *PopulationMap::get(const Point &point)
{
	for (LifeObject *obj : _objects)
		if (obj->get_position() == point)
			return obj;

	return nullptr;
}


const LifeObject *PopulationMap::get(const Point &point) const
{
	for (const LifeObject *obj : _objects)
		if (obj->get_position() == point)
			return obj;

	return nullptr;
}


const PopulationMap::obj_ptr_list PopulationMap::get_neighbours(const Point &point)
{
	obj_ptr_list lst;
	const Point radius(1, 1);
	const Point left_bottom_corner = point - radius;
	const Point right_top_corner = point + radius;

	for (LifeObject *obj : _objects)
	{
		const Point &obj_pos = obj->get_position();

		if ((obj_pos >= left_bottom_corner)
				&& (obj_pos <= right_top_corner))
			lst.push_back(obj);
	}

	return lst;
}


const PopulationMap::obj_ptr_list &PopulationMap::get_objects()
{
	return _objects;
}


const PopulationMap::obj_const_ptr_list &PopulationMap::get_objects() const
{
	obj_const_ptr_list lst;

	for (const LifeObject *obj : _objects)
		lst.push_back(obj);

	return lst;
}


void PopulationMap::push_object(LifeObject *obj)
{
	_objects.push_back(obj);
}


void PopulationMap::clear_objects()
{
	_objects.clear();
}
