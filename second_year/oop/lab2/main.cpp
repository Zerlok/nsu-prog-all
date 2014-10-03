#include "game.h"


int main(int argc, char **argv)
{
	// if (argc == 2)
	// {
	// 	Universe space(atoi(argv[1]));


		
	// 	space.draw();
	// }

	Universe space(10);

	space.init(9, 9, ALIVE);
	space.init(0, 0, ALIVE);
	space.draw();

	return 0;
}