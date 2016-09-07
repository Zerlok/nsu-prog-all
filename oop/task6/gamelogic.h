#ifndef __GAMELOGIC_H__
#define __GAMELOGIC_H__


#include <string>
#include "populationmap.h"
#include "populationmapview.h"


class GameLogic
{
	public:
		// Static.
		static Point map_size;

		// Constructors / Destructor.
		GameLogic();
		GameLogic(const std::string &filename);
		virtual ~GameLogic();

		// Methods.
		void add_objects(int plants_num, int herbivorous_num, int predators_num);
		void run();
		void run(int n);
		void save(const std::string &filename);

	private:
		// Fileds.
		PopulationMap *_map;
		AbstractView *_view;

		// Methods.
		void tick();
		void init_console_graphics();
};


class TextReader
{
	public:
		TextReader(const std::string &filename);
		virtual ~TextReader();

		PopulationMap read_map();
		LifeObject *read_object(const std::string &line);

	private:
		std::ifstream _in;
};


bool action_ptr_comparator(const LifeObject::Action *a1, const LifeObject::Action *a2);


// __GAMELOGIC_H__
#endif
