#include <algorithm>
#include <vector>
#include <unistd.h>

#include "action.h"
#include "gamelogic.h"


Point GameLogic::map_size = Point(40, 20);


GameLogic::GameLogic()
	: _current_map(new PopulationMap(map_size)),
	  _view(new PopulationMapView())
{
	_view->initial_view(*_current_map);

	_current_map->push_object(LifeObject(Point(4, 4), 10));
	_current_map->push_object(LifeObject(Point(5, 5), 10));
	_current_map->push_object(LifeObject(Point(6, 6), 10));
	_current_map->push_object(LifeObject(Point(7, 7), 10));
	_current_map->push_object(LifeObject(Point(6, 12), 10));
	_current_map->push_object(LifeObject(Point(5, 10), 10));
	_current_map->push_object(LifeObject(Point(18, 9), 10));
}


GameLogic::~GameLogic()
{
	delete _current_map;

//	TODO: destroy view - deinit console - all views will lost.
//	delete _view;
}


void GameLogic::run(int ticks_num)
{
	bool is_finished = false;

	while (!is_finished)
	{
		_view->initial_view(*_current_map);

		std::vector<LifeObject::Action*> actions;

		for (LifeObject &obj : _current_map->get_objects())
			actions.push_back(obj.create_action(*_current_map));

		sort(actions.begin(), actions.end());
		for (LifeObject::Action *action : actions)
			action->execute(*_current_map);

		_view->render_map(*_current_map);
		sleep(1);
	}
}
