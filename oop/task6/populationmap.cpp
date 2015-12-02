#include <iostream>
#include "populationmap.h"


PopulationMap::PopulationMap(const Point &corner_position)
	: _corner_position(corner_position)
{
}


PopulationMap::~PopulationMap()
{
	clear_objects();
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

	if (!is_valid_position(point))
		return positions;

	Point left_top_corner = validate_position(point - LifeObject::view_radius);
	Point right_bottom_corner = validate_position(point + LifeObject::view_radius);

	for (int y = left_top_corner['y'];
		 y <= right_bottom_corner['y'];
		 ++y)
	{
		for (int x = left_top_corner['x'];
			 x <= right_bottom_corner['x'];
			 ++x)
		{
			positions.push_back({x, y});
			for (const LifeObject *obj : _objects)
			{
				if ((obj->get_type() != LifeObject::Type::plant)
						&& (obj->get_position() == positions.back()))
				{
					positions.pop_back();
					break;
				}
			}
		}
	}

	return positions;
}


PopulationMap::object_list PopulationMap::get_neighbours(const Point &point)
{
	object_list lst;
	Point left_top_corner = validate_position(point - LifeObject::view_radius);
	Point right_bottom_corner = validate_position(point + LifeObject::view_radius);

	for (LifeObject *obj : _objects)
	{
		const Point &obj_pos = obj->get_position();

		if ((obj_pos >= left_top_corner)
				&& (obj_pos <= right_bottom_corner))
			lst.push_back(obj);
	}

	return lst;
}


const PopulationMap::object_list PopulationMap::get_neighbours(const Point &point) const
{
	object_list lst;
	Point left_top_corner = validate_position(point - LifeObject::view_radius);
	Point right_bottom_corner = validate_position(point + LifeObject::view_radius);

	for (LifeObject *obj : _objects)
	{
		const Point &obj_pos = obj->get_position();

		if ((obj_pos >= left_top_corner)
				&& (obj_pos <= right_bottom_corner))
			lst.push_back(obj);
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


void PopulationMap::push_object(LifeObject *obj)
{
	if (obj == nullptr)
		return;

	_objects.push_back(obj);
}


void PopulationMap::clear_objects()
{
	for (LifeObject *obj : _objects)
		delete obj;
}


Point PopulationMap::validate_position(const Point &position) const
{
	int valid_x = position['x'];
	int valid_y = position['y'];

	if (valid_x >= _corner_position['x'])
		valid_x = _corner_position['x'] - 1;

	if (valid_y >= _corner_position['y'])
		valid_y = _corner_position['y'] - 1;

	if (valid_x < Point::zero['x'])
		valid_x = Point::zero['x'];

	if (valid_y < Point::zero['y'])
		valid_y = Point::zero['y'];

	return Point(valid_x, valid_y);
}
