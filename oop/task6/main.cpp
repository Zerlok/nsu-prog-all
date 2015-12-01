#include <iostream>
using namespace std;


#include "gamelogic.h"


int main()
{
//	Game from file
//	GameLogic game(argv[1]);
	GameLogic game;

	game.init_game(4, 4, 8);
	game.run();

	return 0;
}
