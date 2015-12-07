#ifndef __CONFIG_H__
#define __CONFIG_H__


namespace Config
{
	// LifeObject constants.
	static const int object_dead_ttl = 0;
	static const int object_min_damage = 0;
	static const int object_min_weight = 0;
	static const int object_min_ttl_for_reproducing = 3;
	static const int object_reproducing_ratio = 2;
	static const int object_hp_for_kill = 3;
	static const Point object_view_radius = Point(1, 1);

	// Plant constants.
	static const int plant_born_ttl = 5;
	static const int plant_damage = 0;
	static const int plant_mass = 5;
	static const int plant_reproduction_ratio = 4;

	// Herbivorous constants.
	static const int herbivorous_born_ttl = 13;
	static const int herbivorous_damage = 0;
	static const int herbivorous_mass = 15;
	static const int herbivorous_reproduction_ratio = 3;
	static const int herbivorous_hungry_ttl = 5;

	// Predators constants.
	static const int predator_born_ttl = 23;
	static const int predator_damage = 5;
	static const int predator_mass = 13;
	static const int predator_reproduction_ratio = 3;
	static const int predator_hungry_ttl = 12;

	// Map constants.
	static const int map_height = 30;
	static const int map_width = map_height * 2;

	// Game ticking.
	static const int game_ticking_interval = 1;
}


// __CONFIG_H__
#endif
