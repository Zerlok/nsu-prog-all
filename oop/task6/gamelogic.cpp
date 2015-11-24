#include <algorithm>

#include "gamelogic.h"


Point GameLogic::map_size = Point(8, 8);


GameLogic::GameLogic()
	: _current_map(new PopulationMap(map_size)),
	  _next_map(new PopulationMap(map_size)),
	  _view(new PopulationMapView())
{
	// TODO: read config.
}


GameLogic::~GameLogic()
{
	delete _current_map;
	delete _next_map;
}


void GameLogic::run(int ticks_num)
{
	for (int i = 0; i < ticks_num; ++i)
	{
		for (const LifeObject *obj : _current_map->get_objects())
			tick_object(*obj);

		std::swap(_current_map, _next_map);
		_view->render(*_current_map);
		_next_map->clear_objects();
	}
}


void GameLogic::tick_object(const LifeObject &current_obj)
{
	LifeObject *next_obj = new LifeObject(current_obj);
	_next_map->push_object(next_obj);

	const PopulationMap::obj_ptr_list &obj_neighbours = _current_map->get_neighbours(current_obj.get_position());

	next_obj->make_action(obj_neighbours);
	next_obj->make_older();
}
