#include "main.h"
#include "lifeform.h"
#include "universe.h"
#include "gamelogic.h"


int main(int argc, char **argv)
{
	Game lifegame(argc, argv);

	lifegame.run();

	return 0;
}
