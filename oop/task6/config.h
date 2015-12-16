#ifndef __CONFIG_H__
#define __CONFIG_H__


#include "point.h"


namespace Config
{
	// LifeObject constants.
	const int object_dead_ttl = 0;
	const int object_min_damage = 0;
	const int object_min_mass = 0;
	const int object_min_ttl_for_reproducing = 3;
	const int object_child_ttl_reproduction_ratio = 2;
	const int object_parent_ttl_reproduction_ratio = 2;
	const int object_ttl_for_eating = 3;
	const Point object_walk_radius = Point(1, 1);

	// Plant constants.
	const bool plant_is_dieable = true;
	const int plant_born_ttl = 11;
	const int plant_damage = 0;
	const int plant_mass = 7;
	const int plant_reproduction_ratio = 4;

	// Herbivorous constants.
	const int herbivorous_born_ttl = 11;
	const int herbivorous_damage = 0;
	const int herbivorous_mass = 8;
	const int herbivorous_reproduction_ratio = 3;
	const int herbivorous_hungry_ttl = 4;

	// Predators constants.
	const int predator_born_ttl = 18;
	const int predator_damage = 5;
	const int predator_mass = 9;
	const int predator_reproduction_ratio = 3;
	const int predator_hungry_ttl = 11;

	// Map constants.
	const int map_height = 30;
	const int map_width = map_height * 2;

	// Game ticking.
	const std::string game_default_savefile = "population_save.txt";
	const int game_ticking_interval = 1;

	const char file_data_separator = '|';
}


// __CONFIG_H__
#endif
