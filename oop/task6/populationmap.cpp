#include <iostream>
#include "populationmap.h"


PopulationMap::PopulationMap(int width, int height)
	: _corner_position({width, height}),
	  _plants_num(0),
	  _herbivorous_num(0),
	  _predators_num(0)
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


int PopulationMap::get_plants_num() const
{
	return _plants_num;
}


int PopulationMap::get_herbivorous_num() const
{
	return _herbivorous_num;
}


int PopulationMap::get_predators_num() const
{
	return _predators_num;
}


int PopulationMap::get_total_objects_num() const
{
	return (_plants_num + _herbivorous_num + _predators_num);
}


bool PopulationMap::is_valid_position(const Point &position) const
{
	return ((position >= Point::zero)
			&& (position < _corner_position));
}


std::vector<Point> PopulationMap::get_free_positions(
		const Point &point,
		bool except_plants,
		bool except_herbivorous,
		bool except_preadators) const
{
	std::vector<Point> positions;

	if (!is_valid_position(point))
		return positions;

	const Point left_top_corner = validate_position(point - Config::object_walk_radius);
	const Point right_bottom_corner = validate_position(point + Config::object_walk_radius);
	const objects_list &neighbours = get_neighbours(point);

	for (int y = left_top_corner['y'];
		 y <= right_bottom_corner['y'];
		 ++y)
	{
		for (int x = left_top_corner['x'];
			 x <= right_bottom_corner['x'];
			 ++x)
		{
			bool valid_position = true;
			positions.push_back({x, y});
			for (const LifeObject *obj : neighbours)
			{
				if (obj->get_position() == positions.back())
				{
					switch (obj->get_type())
					{
						case LifeObject::Type::plant:
							valid_position = valid_position && !except_plants;
							break;
						case LifeObject::Type::herbivorous:
							valid_position = valid_position && !except_herbivorous;
							break;
						case LifeObject::Type::predator:
							valid_position = valid_position && !except_preadators;
							break;
						default:
							break;
					}

					if (!valid_position)
					{
						positions.pop_back();
						break;
					}
				}
			}
		}
	}

	return positions;
}


PopulationMap::objects_list PopulationMap::get_neighbours(const Point &point)
{
	objects_list lst;
	Point left_top_corner = validate_position(point - Config::object_walk_radius);
	Point right_bottom_corner = validate_position(point + Config::object_walk_radius);

	for (LifeObject *obj : _objects)
	{
		const Point &obj_pos = obj->get_position();

		if ((obj_pos >= left_top_corner)
				&& (obj_pos <= right_bottom_corner))
			lst.push_back(obj);
	}

	return lst;
}


const PopulationMap::objects_list PopulationMap::get_neighbours(const Point &point) const
{
	objects_list lst;
	Point left_top_corner = validate_position(point - Config::object_walk_radius);
	Point right_bottom_corner = validate_position(point + Config::object_walk_radius);

	for (LifeObject *obj : _objects)
	{
		const Point &obj_pos = obj->get_position();

		if ((obj_pos >= left_top_corner)
				&& (obj_pos <= right_bottom_corner))
			lst.push_back(obj);
	}

	return lst;
}


PopulationMap::objects_list &PopulationMap::get_objects()
{
	return _objects;
}


const PopulationMap::objects_list &PopulationMap::get_objects() const
{
	return _objects;
}


void PopulationMap::insert_object(LifeObject *obj)
{
	if (obj == nullptr)
		return;

	switch (obj->get_type())
	{
		case LifeObject::Type::plant:
			++_plants_num;
			break;
		case LifeObject::Type::herbivorous:
			++_herbivorous_num;
			break;
		case LifeObject::Type::predator:
			++_predators_num;
			break;
		default:
			break;
	}

	if (_objects.empty())
	{
		_objects.push_back(obj);
		return;
	}
	else if (obj->operator<(*(_objects.front())))
	{
		_objects.insert(_objects.begin(), obj);
		return;
	}

	for (objects_list::iterator it = _objects.begin();
		 it != _objects.end();
		 ++it)
	{
		LifeObject &o = *(*it);
		if (obj->operator<=(o))
		{
			_objects.insert(it, obj);
			return;
		}
	}

	_objects.push_back(obj);
}


PopulationMap::objects_list::iterator PopulationMap::erase_object(objects_list::iterator &it)
{
	LifeObject *obj = (*it);

	switch (obj->get_type())
	{
		case LifeObject::Type::plant:
			--_plants_num;
			break;
		case LifeObject::Type::herbivorous:
			--_herbivorous_num;
			break;
		case LifeObject::Type::predator:
			--_predators_num;
			break;
	}

	delete obj;
	return _objects.erase(it);
}


void PopulationMap::clear_objects()
{
	for (LifeObject *obj : _objects)
		delete obj;

	_objects.clear();

	_plants_num = 0;
	_herbivorous_num = 0;
	_predators_num = 0;
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
