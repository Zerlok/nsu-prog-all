#ifndef __GAMELOGIC_H__
#define __GAMELOGIC_H__


#include "populationmap.h"
#include "populationmapview.h"


class GameLogic
{
	public:
		// Static.
		static Point map_size;

		// Constructors / Destructor.
		GameLogic();
		virtual ~GameLogic();

		// Methods.
		void init_life(int plants_num, int herbivorous_num, int predators_num);
		void run();
		void tick();

	private:
		// Fileds.
		PopulationMap *_map;
		AbstractView *_view;
};


// __GAMELOGIC_H__
#endif
