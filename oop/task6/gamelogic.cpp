#include <algorithm>
#include <set>
#include <vector>
#include <unistd.h>
#include <time.h>

#include "console.h"
#include "action.h"
#include "plant.h"
#include "herbivorous.h"
#include "predator.h"

#include "gamelogic.h"
#include "config.h"


GameLogic::GameLogic()
{
	srand(time(NULL));

	setenv("TERM", "xterm", 1);
	con_init();
	con_hideCursor();

	_map = new PopulationMap(Config::map_width, Config::map_height);
	_view = new ConsoleView(*_map);
}


GameLogic::~GameLogic()
{
	delete _map;
	delete _view;

	con_deinit();
}


void GameLogic::add_objects(int plants_num, int herbivorous_num, int predators_num)
{
	int width = _map->get_width();
	int height = _map->get_height();
	for (int i = 0; i < plants_num; ++i)
		_map->insert_object(
				new Plant(Point(rand() % width, rand() % height))
		);

	for (int i = 0; i < herbivorous_num; ++i)
		_map->insert_object(
				new Herbivorous(Point(rand() % width, rand() % height))
		);

	for (int i = 0; i < predators_num; ++i)
		_map->insert_object(
				new Predator(Point(rand() % width, rand() % height))
		);
}


void GameLogic::run()
{
	bool is_finished = false;
	bool is_paused = true;

	_view->initialize_map_view();
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
			sleep(Config::game_ticking_interval);
		}
	}
}


void GameLogic::run(int n)
{
	_view->initialize_map_view();
	_view->render_map();

	for (int i = 0; i < n; ++i)
	{
		tick();
		sleep(1);
	}
}


void GameLogic::tick()
{
	_view->clear_map();

	PopulationMap::objects_list &objects = _map->get_objects();
	std::vector<LifeObject::Action*> objects_actions;

	for (PopulationMap::objects_list::iterator it = objects.begin();
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
		else if (obj->get_mass() <= 0)
		{
			it = _map->erase_object(it);
			--it;
		}
	}

	std::sort(objects_actions.begin(), objects_actions.end(), action_ptr_comparator);
	for (LifeObject::Action *action : objects_actions)
	{
		action->execute(*_map);
		delete action;
	}

	_view->render_map();
}


bool action_ptr_comparator(const LifeObject::Action *a1, const LifeObject::Action *a2)
{
	return ((*a1) > (*a2));
}
