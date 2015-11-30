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
		~GameLogic();

		// Methods.
		void run(int ticks_num=1);

	private:
		// Fileds.
		PopulationMap *_current_map;
		PopulationMapView *_view;
};


// __GAMELOGIC_H__
#endif
