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
		void run();
		void tick(int ticks_num=1);

	private:
		// Fileds.
		PopulationMap *_current_map;
		AbstractView *_view;
};


// __GAMELOGIC_H__
#endif
