#include <algorithm>

#include "gamelogic.h"


Point GameLogic::map_size = Point(20, 20);


GameLogic::GameLogic()
	: _current_map(new PopulationMap(map_size)),
	  _next_map(new PopulationMap(map_size)),
	  _view(new PopulationMapView())
{
	_view->initial_view(*_current_map);

	_current_map->push_object(LifeObject(Point(4, 4), 10));
	_current_map->push_object(LifeObject(Point(5, 5), 10));
	_current_map->push_object(LifeObject(Point(6, 6), 10));
}


GameLogic::~GameLogic()
{
	delete _current_map;
	delete _next_map;

//	TODO: destroy view - deinit console - all views will lost.
//	delete _view;
}


void GameLogic::run(int ticks_num)
{
	_view->render(*_current_map);

//	for (int i = 0; i < ticks_num; ++i)
//	{
//		for (const LifeObject *obj : _current_map->get_objects())
//			tick_object(*obj);

//		std::swap(_current_map, _next_map);
//		_view->render(*_current_map);
//		_next_map->clear_objects();
//	}
}


void GameLogic::tick_object(const LifeObject &current_obj)
{
	LifeObject next_obj(current_obj);
	next_obj.make_action(*_current_map);
	_next_map->push_object(next_obj);
}
