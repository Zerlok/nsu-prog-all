#include <iostream>
using namespace std;


#include "predator.h"
#include "gamelogic.h"


int main()
{
//	Game from file
//	GameLogic game(argv[1]);
	GameLogic game;

	game.init_game(15, 10, 12);
//	game.run();
	for (int i = 0; i < 20; ++i)
		game.tick();

	return 0;
}
