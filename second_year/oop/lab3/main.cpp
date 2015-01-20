#include "main.h"

#include "strategy.h"
#include "factory.h"
#include "mode.h"
#include "game.h"


int main(const int argc, const char **argv)
{
	Game prisoners_game(argc, argv);

	prisoners_game.run();

	return 0;
}