#include <iostream>
using namespace std;


#include "gamelogic.h"


int main()
{
//	Game from file
//	GameLogic game(argv[1]);
//	GameLogic game;

//	game.run();

	for (int i = 0; i < 20; ++i)
		cout << rand() % 8 << endl;

	return 0;
}
