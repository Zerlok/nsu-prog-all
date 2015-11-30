#include <algorithm>
#include <vector>
#include <unistd.h>
#include <time.h>

#include "console.h"
#include "action.h"
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

	for (int i = 0; i < (rand() + 5) % 10; ++i)
		_current_map->push_object(LifeObject(Point(rand() % map_size['x'], rand() % map_size['y']), 10));
}


GameLogic::~GameLogic()
{
	delete _current_map;
	delete _view;

	con_deinit();
}


void GameLogic::run()
{
	bool is_finished = false;
	bool is_paused = false;

	while (!is_finished)
	{
		if (con_keyPressed())
		{
			switch (con_getKey())
			{
				case ' ':
					is_paused = !is_paused;
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

	for (LifeObject &obj : _current_map->get_objects())
		actions.push_back(obj.create_action(*_current_map));

	sort(actions.begin(), actions.end());
	for (LifeObject::Action *action : actions)
	{
		action->execute(*_current_map);
		delete action;
	}

	_view->render_map();
	sleep(1);
}
