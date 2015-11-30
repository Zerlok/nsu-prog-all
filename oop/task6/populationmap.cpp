#include <iostream>
#include "populationmap.h"


PopulationMap::PopulationMap(const Point &corner_position)
	: _corner_position(corner_position)
{
}


PopulationMap::~PopulationMap()
{
}


int PopulationMap::get_height() const
{
	return _corner_position['y'];
}


int PopulationMap::get_width() const
{
	return _corner_position['x'];
}


bool PopulationMap::is_valid_position(const Point &position) const
{
	return ((position >= Point::zero)
			&& (position < _corner_position));
}


std::vector<Point> PopulationMap::get_free_positions(const Point &point) const
{
	std::vector<Point> positions;

	Point left_top_corner = point - LifeObject::view_radius;
	Point right_bottom_corner = point + LifeObject::view_radius;

	if (left_top_corner < Point::zero)
		left_top_corner = Point::zero;

	if (right_bottom_corner >= _corner_position)
		right_bottom_corner = _corner_position;

//	std::cout << left_top_corner << "->" << right_bottom_corner << std::endl;

	for (int y = left_top_corner['y'];
		 y <= right_bottom_corner['y'];
		 ++y)
	{
		for (int x = left_top_corner['x'];
			 x <= right_bottom_corner['x'];
			 ++x)
		{
			positions.push_back({x, y});
			for (const LifeObject &obj : _objects)
			{
				if (obj.get_position() == positions.back())
				{
					positions.pop_back();
					break;
				}
			}
		}
	}

	return positions;
}


PopulationMap::object_ptr_list PopulationMap::get_neighbours(const Point &point)
{
	object_ptr_list lst;
	Point left_bottom_corner = point - LifeObject::view_radius;
	Point right_top_corner = point + LifeObject::view_radius;

	if (!(left_bottom_corner >= Point::zero))
		left_bottom_corner = Point::zero;

	if (!(right_top_corner <= _corner_position))
		right_top_corner = _corner_position;

	for (LifeObject &obj : _objects)
	{
		const Point &obj_pos = obj.get_position();

		if ((obj_pos >= left_bottom_corner)
				&& (obj_pos <= right_top_corner))
			lst.push_back(&obj);
	}

	return lst;
}


const PopulationMap::object_ptr_list PopulationMap::get_neighbours(const Point &point) const
{
	object_ptr_list lst;
	Point left_bottom_corner = point - LifeObject::view_radius;
	Point right_top_corner = point + LifeObject::view_radius;

	if (!(left_bottom_corner >= Point::zero))
		left_bottom_corner = Point::zero;

	if (!(right_top_corner <= _corner_position))
		right_top_corner = _corner_position;

	for (LifeObject obj : _objects)
	{
		const Point &obj_pos = obj.get_position();

		if ((obj_pos >= left_bottom_corner)
				&& (obj_pos <= right_top_corner))
			lst.push_back(&obj);
	}

	return lst;
}


PopulationMap::object_list &PopulationMap::get_objects()
{
	return _objects;
}


const PopulationMap::object_list &PopulationMap::get_objects() const
{
	return _objects;
}


void PopulationMap::push_object(const LifeObject &obj)
{
	_objects.push_back(obj);
}


void PopulationMap::clear_objects()
{
	_objects.clear();
}
