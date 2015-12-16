#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
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
	_map = new PopulationMap(Config::map_width, Config::map_height);

	init_console_graphics();
	_view = new ConsoleView(*_map);
}


GameLogic::GameLogic(const std::string &filename)
{

	TextReader reader(filename);
	_map = new PopulationMap(reader.read_map());

	init_console_graphics();
	_view = new ConsoleView(*_map);
}


GameLogic::~GameLogic()
{
	delete _view;
	con_deinit();

	save(Config::game_default_savefile);
	delete _map;
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
				default:
					break;
			}
		}
		else if (!is_paused)
		{
			tick();
			_view->initialize_map_view();
			_view->render_map();

			sleep(Config::game_ticking_interval);
		}
	}
}


void GameLogic::run(int n)
{
	_view->initialize_map_view();
	_view->render_map();

	for (int i = 0; i < n; ++i)
		tick();

	_view->initialize_map_view();
	_view->render_map();
	while (!con_keyPressed());
}


void GameLogic::save(const std::string &filename)
{
	std::ofstream output(filename);
	TextView view(*_map, output);

	view.initialize_map_view();
	view.render_map();

	output.close();
}


void GameLogic::tick()
{
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
		else if (obj->is_eatable())
		{
			obj->decrement_mass();
		}
		else
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
}


void GameLogic::init_console_graphics()
{
	srand(time(NULL));

	setenv("TERM", "xterm", 1);
	con_init();
	con_hideCursor();
}


TextReader::TextReader(const std::string &filename)
	: _in(filename)
{
}


TextReader::~TextReader()
{
	_in.close();
}


PopulationMap TextReader::read_map()
{
	int width;
	int height;
	char tmp;
	std::stringstream ss;
	std::string line;

	_in >> width >> tmp >> height;
	PopulationMap map(width, height);

	while (getline(_in, line))
		map.insert_object(read_object(line));

	return map;
}


LifeObject *TextReader::read_object(const std::string &line)
{
	if (line.empty())
		return nullptr;

	size_t sep_pos = line.find(Config::file_data_separator);
	if (sep_pos == std::string::npos)
		return nullptr;

	std::stringstream ss;
	char tmp;

	LifeObject::Type type;
	int ttl;
	int dmg;
	int mass;
	Point pos;

	type = get_type_by_name(line.substr(0, sep_pos));
	ss.str(line.substr(sep_pos + 1));
	ss >> ttl >> tmp >> dmg >> tmp >> mass >> tmp >> pos;

	switch (type)
	{
		case LifeObject::Type::plant:
			return new Plant(pos, ttl, dmg, mass);

		case LifeObject::Type::herbivorous:
			return new Herbivorous(pos, ttl, dmg, mass);

		case LifeObject::Type::predator:
			return new Predator(pos, ttl, dmg, mass);

		default:
			return nullptr;
	}
}


bool action_ptr_comparator(const LifeObject::Action *a1, const LifeObject::Action *a2)
{
	return ((*a1) > (*a2));
}
