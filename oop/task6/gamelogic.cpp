#include <algorithm>
#include <vector>
#include <unistd.h>
#include <time.h>

#include "console.h"
#include "action.h"
#include "plant.h"
#include "herbivorous.h"
#include "predator.h"

#include "gamelogic.h"


const int height = 20;
Point GameLogic::map_size = Point(2 * height, height);


GameLogic::GameLogic()
{
	srand(time(NULL));

	setenv("TERM", "xterm", 1);
	con_init();
	con_hideCursor();

	_map = new PopulationMap(map_size);
	_view = new ConsoleView(*_map);
}


GameLogic::~GameLogic()
{
	delete _map;
	delete _view;

	con_deinit();
}


void GameLogic::init_life(int plants_num, int herbivorous_num, int predators_num)
{
	for (int i = 0; i < plants_num; ++i)
		_map->push_object(
				new Plant(
					Point(rand() % map_size['x'], rand() % map_size['y']),
					5,
					1,
					5
				)
		);

	for (int i = 0; i < herbivorous_num; ++i)
		_map->push_object(
				new Herbivorous(
					Point(rand() % map_size['x'], rand() % map_size['y']),
					8,
					1,
					8
				)
		);

	for (int i = 0; i < predators_num; ++i)
		_map->push_object(
				new Predator(
					Point(rand() % map_size['x'], rand() % map_size['y']),
					12,
					4,
					10
				)
		);
}


void GameLogic::run()
{
	bool is_finished = false;
	bool is_paused = true;

	_view->initial_view();
	_view->render_map();

	while (!is_finished)
	{
		if (con_keyPressed())
		{
			switch (con_getKey())
			{
				case 't':
					tick();
					break;
				case 'p':
					is_paused = !is_paused;
					break;
				case CON_KEY_ESCAPE:
					is_finished = true;
					break;
			}
		}
		else if (!is_paused)
		{
			tick();
			usleep(180000);
		}
	}
}


void GameLogic::tick()
{
	_view->initial_view();

	PopulationMap::object_list &objects = _map->get_objects();
	std::vector<LifeObject::Action*> objects_actions;

	for (PopulationMap::object_list::iterator it = objects.begin();
		 it != objects.end();
		 ++it)
	{
		LifeObject *obj = (*it);
		if (obj->is_alive())
		{
			LifeObject::Action *action = obj->create_action(*_map);
			if (action != nullptr)
				objects_actions.push_back(action);
		}
		else if (obj->get_weight() == 0)
		{
			it = objects.erase(it);
			--it;
			delete obj;
		}
	}

	sort(objects_actions.begin(), objects_actions.end());
	for (LifeObject::Action *action : objects_actions)
	{
		action->execute(*_map);
		delete action;
	}

	_view->render_map();
}
