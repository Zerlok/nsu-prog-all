#include <iostream>
using namespace std;

#include "gamelogic.h"


int main(int argc, char *argv[])
{
//	Game from file
	GameLogic game;
	game.add_objects(15, 10, 12);

	if (argc > 1)
		game.run(stoi(argv[1]));
	else
		game.run();

	return 0;
}
