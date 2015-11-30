#include <iostream>
using namespace std;


#include "gamelogic.h"


int main()
{
//	Game from file
//	GameLogic game(argv[1]);
	GameLogic game;

//	game.tick(1);
	game.run();

	return 0;
}
