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


Point GameLogic::map_size = Point(40, 20);


GameLogic::GameLogic()
	: _current_map(new PopulationMap(map_size))
{
	srand(time(NULL));

	setenv("TERM", "xterm", 1);
	con_init();
	con_hideCursor();

	_view = new ConsoleView(*_current_map);
}


GameLogic::~GameLogic()
{
	delete _current_map;
	delete _view;

	con_deinit();
}


void GameLogic::init_game(int plants_num, int herbivorous_num, int predators_num)
{
	for (int i = 0; i < plants_num; ++i)
		_current_map->push_object(
				new Plant(
					Point(rand() % map_size['x'], rand() % map_size['y']),
					10,
					1,
					8
				)
		);

	for (int i = 0; i < herbivorous_num; ++i)
		_current_map->push_object(
				new Herbivorous(
					Point(rand() % map_size['x'], rand() % map_size['y']),
					15,
					1,
					10
				)
		);

	for (int i = 0; i < predators_num; ++i)
		_current_map->push_object(
				new Predator(
					Point(rand() % map_size['x'], rand() % map_size['y']),
					15,
					3,
					15
				)
		);
}


void GameLogic::run()
{
	bool is_finished = false;
	bool is_paused = true;

	while (!is_finished)
	{
		if (con_keyPressed())
		{
			switch (con_getKey())
			{
				case ' ':
					tick();
//					is_paused = !is_paused;
					break;
				case CON_KEY_ESCAPE:
					is_finished = true;
					break;
			}
		}

		if (!is_paused)
			tick();
	}
}


void GameLogic::tick(int ticks_num)
{
	_view->initial_view();

	std::vector<LifeObject::Action*> actions;

	for (LifeObject *obj : _current_map->get_objects())
	{
		if (obj->is_alive())
			actions.push_back(obj->create_action(*_current_map));
	}

	sort(actions.begin(), actions.end());
	for (LifeObject::Action *action : actions)
	{
		if (action != nullptr)
		{
			action->execute(*_current_map);
			delete action;
		}
	}

	_view->render_map();
	sleep(1);
}
