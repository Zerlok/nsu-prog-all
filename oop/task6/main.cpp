#include <iostream>
using namespace std;


#include "gamelogic.h"


int main()
{
//	Game from file
//	GameLogic game(argv[1]);
	GameLogic game;

//	game.tick(1);
	game.init_game(15, 8, 4);
	game.run();

	return 0;
}
