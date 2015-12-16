#include <iostream>
using namespace std;

#include "gamelogic.h"


int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		GameLogic game(argv[1]);
		game.run();
	}
	else
	{
		cout << "Save file was not given, running the default game." << endl;
		GameLogic game;
		game.add_objects(15, 10, 12);
		game.run();
	}

	return 0;
}
