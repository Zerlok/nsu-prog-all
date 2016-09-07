#ifndef __CONFIG_H__
#define __CONFIG_H__


#include "point.h"


namespace Config
{
	// LifeObject constants.
	static const int object_dead_ttl = 0;
	static const int object_min_damage = 0;
	static const int object_min_mass = 0;
	static const int object_min_ttl_for_reproducing = 3;
	static const int object_child_ttl_reproduction_ratio = 2;
	static const int object_parent_ttl_reproduction_ratio = 2;
	static const int object_ttl_for_eating = 3;
	static const Point object_walk_radius = Point(1, 1);

	// Plant constants.
	static const bool plant_is_dieable = true;
	static const int plant_born_ttl = 11;
	static const int plant_damage = 0;
	static const int plant_mass = 7;
	static const int plant_reproduction_ratio = 4;

	// Herbivorous constants.
	static const int herbivorous_born_ttl = 11;
	static const int herbivorous_damage = 0;
	static const int herbivorous_mass = 8;
	static const int herbivorous_reproduction_ratio = 3;
	static const int herbivorous_hungry_ttl = 4;

	// Predators constants.
	static const int predator_born_ttl = 18;
	static const int predator_damage = 5;
	static const int predator_mass = 9;
	static const int predator_reproduction_ratio = 3;
	static const int predator_hungry_ttl = 11;

	// Map constants.
	static const int map_height = 30;
	static const int map_width = map_height * 2;

	// Game ticking.
	static const std::string game_default_savefile = "pop.save";
	static const int game_ticking_interval = 1;

	static const char file_data_separator = '|';
}


// __CONFIG_H__
#endif
